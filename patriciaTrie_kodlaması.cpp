#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Patricia trie'de her düğüm, kendisine gelen kenarın etiketini (string),
// kelime sonu olup olmadığını belirten bayrağı (isEnd) ve çocuk düğümleri tutar.
struct TrieNode {
    string label;
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    
    TrieNode(const string &lab = "") : label(lab), isEnd(false) {}
};

class PatriciaTrie {
private:
    TrieNode* root;
    
    // Kelimeyi silmeye yarayan yardımcı fonksiyon (recursive).
    // pos: word içerisindeki eşleşmeye başlanacak pozisyon.
    // Fonksiyon, eğer alt düğüm silinebilir (hafızadan kaldırılabilir) ise true döner.
    bool removeUtil(TrieNode* node, const string &word, int pos) {
        // Eğer kelimenin sonuna geldiysek
        if (pos == word.size()) {
            if (!node->isEnd)
                return false; // Kelime bulunamadı
            node->isEnd = false;
            return node->children.empty();
        }
        char key = word[pos];
        auto it = node->children.find(key);
        if (it == node->children.end())
            return false; // Kelime mevcut değil.
        
        TrieNode* child = it->second;
        int i = 0;
        // Mevcut kenar etiketinin (child->label) word içindeki kısmıyla ortak prefix uzunluğunu bulur.
        while(i < child->label.size() && pos + i < word.size() && word[pos + i] == child->label[i])
            i++;
        if (i != child->label.size())
            return false; // Eşleşme detayında uyuşmazlık: aranan kelime yok.
        
        // Child düğüm altında silme işlemini uygulanır.
        bool shouldDeleteChild = removeUtil(child, word, pos + i);
        
        if (shouldDeleteChild) {
            // İlgili düğüm alt ağacını sildikten sonra child'ı kaldırır.
            node->children.erase(key);
            delete child;
            
            // Eğer bu düğüm (node), root değil, kelime sonu değil ve çocuk sayısı 1 ise,
            // düğümle tek çocuk birleşmesi (merge) yapılabilir.
            if (node != root && node->children.size() == 1 && !node->isEnd) {
                auto onlyChildIt = node->children.begin();
                TrieNode* onlyChild = onlyChildIt->second;
                node->label += onlyChild->label;  // kenar etiketlerini birleştirir.
                node->isEnd = onlyChild->isEnd;
                node->children = move(onlyChild->children);
                delete onlyChild;
            }
            return node->children.empty() && !node->isEnd;
        } else {
            // Silme sonrası child için de merge yapılabilir: Eğer child noktası
            // terminal değil ve tek bir çocuğa sahipse, bu çocuğun kenar etiketi ile birleştirir.
            if (child->children.size() == 1 && !child->isEnd) {
                auto onlyChildIt = child->children.begin();
                TrieNode* onlyChild = onlyChildIt->second;
                child->label += onlyChild->label;
                child->isEnd = onlyChild->isEnd;
                child->children = move(onlyChild->children);
                delete onlyChild;
            }
            return false;
        }
    }
    
    // Trie ağacını yazdırmak için (debug/inceleme amaçlı) yardımcı fonksiyon.
    void printUtil(TrieNode* node, string prefix) {
        if (node->isEnd)
            cout << prefix << endl;
        for (auto &p : node->children) {
            printUtil(p.second, prefix + p.second->label);
        }
    }
    
    // Bellek temizleme işlemi: Düğüm ve alt düğümleri de serbest bırakır.
    void deleteAll(TrieNode* node) {
        for(auto &p : node->children)
            deleteAll(p.second);
        delete node;
    }
    
public:
    PatriciaTrie() {
        root = new TrieNode();
    }
    
    ~PatriciaTrie() {
        deleteAll(root);
    }
    
    // Kelime ekleme fonksiyonu:
    // Anahtar kelimenin kalan kısmını uygun çocuğa ekleyip,
    // varsa kenar üzerinde ortak prefix'e göre bölme (split) yapar.
    void insert(const string &word) {
        TrieNode* node = root;
        int pos = 0;
        while (pos < word.size()) {
            char key = word[pos];
            // Henüz bu harfle başlayan bir kenar yoksa
            if (node->children.find(key) == node->children.end()) {
                TrieNode* newNode = new TrieNode(word.substr(pos));
                newNode->isEnd = true;
                node->children[key] = newNode;
                return;
            }
            
            TrieNode* child = node->children[key];
            int i = 0;
            // Mevcut kenarın etiketindeki ortak prefix'i bulur.
            while(i < child->label.size() && pos + i < word.size() && word[pos+i] == child->label[i])
                i++;
            
            // Eğer kenarın kısmı kelime parçasından daha uzunsa: bölme (split) yapar.
            if (i < child->label.size()) {
                TrieNode* splitNode = new TrieNode(child->label.substr(0, i));
                node->children[key] = splitNode;
                child->label = child->label.substr(i);
                splitNode->children[child->label[0]] = child;
                
                // Eklenmek istenen kelimenin de kalan kısmını ekler.
                if (pos + i < word.size()) {
                    TrieNode* newNode = new TrieNode(word.substr(pos+i));
                    newNode->isEnd = true;
                    splitNode->children[newNode->label[0]] = newNode;
                } else {
                    splitNode->isEnd = true;
                }
                return;
            }
            
            // Mevcut kenarın tamamı eşleştiyse, kelimeye devam eder.
            pos += i;
            node = child;
        }
        node->isEnd = true;
    }
    
    // Kelime arama fonksiyonu:
    // Adım adım kenar etiketlerini kontrol ederek kelime varsa true, yoksa false döner.
    bool search(const string &word) {
        TrieNode* node = root;
        int pos = 0;
        while (pos < word.size()) {
            char key = word[pos];
            if (node->children.find(key) == node->children.end())
                return false;
            TrieNode* child = node->children[key];
            int i = 0;
            while(i < child->label.size() && pos + i < word.size() && word[pos+i] == child->label[i])
                i++;
            if(i != child->label.size())
                return false;
            pos += i;
            node = child;
        }
        return node->isEnd;
    }
    
    // Kelime silme fonksiyonu:
    // removeUtil() çağrılarak silme işlemini gerçekleştirir.
    bool remove(const string &word) {
        return removeUtil(root, word, 0);
    }
    
    // Trie'nin içerdiği tüm kelimeleri ekrana yazdırır.
    void print() {
        printUtil(root, "");
    }
};

//Kullanıcının kullanacağı menü fonksiyonudur.
int main() {
    PatriciaTrie trie;
    int choice;
    string word;
    
    while (true) {
        cout << "\n1. Ekle\n2. Sil\n3. Arama\n4. Yazdir\n5. Cikis\nSeciminizi yapiniz: ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Eklenecek kelimeyi giriniz: ";
            cin >> word;
            trie.insert(word);
            cout << word << " eklendi.\n";
        }
        else if (choice == 2) {
            cout << "Silinecek kelimeyi giriniz: ";
            cin >> word;
            if(trie.remove(word))
                cout << word << " silindi.\n";
            else
                cout << word << " bulunamadi.\n";
        }
        else if (choice == 3) {
            cout << "Aranacak kelimeyi giriniz: ";
            cin >> word;
            if(trie.search(word))
                cout << word << " bulundu.\n";
            else
                cout << word << " bulunamadi.\n";
        }
        else if (choice == 4) {
            cout << "Trie icerigi:\n";
            trie.print();
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Gecersiz secim.\n";
        }
    }
    
    return 0;
}
