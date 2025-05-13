# Patricia Tree (PATRICIA) Algoritması

PATRICIA ağacı (Pratik Algoritma ile Alfanümerik Kodlanmış Bilgiyi Alma - Practical Algorithm To Retreeve Information Coded in Alphanumeric) özellikle string verilerini verimli bir şekilde saklamak ve almak için kullanılan sıkıştırılmış bir tree  veri yapısıdır Standart tree yapılarının aksine, tek çocuğu olan düğümleri birleştirerek yerden tasarruf sağlar. Bu sayede özellikle seyrek veri kümelerinde veya uzun ortak ön eklere sahip string bellek kullanımını azaltır.

## Algoritmanın Kategorisi

Patricia Tree, temel olarak bir **Arama** veri yapısıdır. Tree tabanlı veri yapılarının bir alt türü olarak sınıflandırılabilir ve özellikle string işlemleri ve ön ek tabanlı aramalarda kullanılır

## Çözüm Yaklaşımı

Patricia Tree'nin temel çözüm yaklaşımı standart bir tree'deki gereksiz düğümleri ortadan kaldırarak yapıyı sıkıştırmaktır. Standart bir tree'de bir anahtarın her bir karakteri  ayrı bir düğüme karşılık gelebilir. Ancak bir düğümün yalnızca tek bir çocuğu varsa bu durum zincirleme düğümlere yol açar ve bellek israfına neden olur. Patricia Tree bu tür zincirleme düğümleri tek bir kenarda birleştirir Her düğüm, hangi bitin  test edileceğini belirten bir indeks bilgisi tutar. Bu sayede, yalnızca dallanma noktalarında yeni düğümler oluşturulur. Karşılaştırmalar anahtarlar arasındaki ilk farkllılaşan bit üzerinden yapılır.

## Ne Zaman ve Neden Kullanılır?

*   **Bellek Verimliliği Gerektiğinde:** Standart tree'lere kıyasla önemli ölçüde daha az bellek kullanır çünkü tek çocuklu düğüm zincirlerini sıkıştırır. Bu büyük veri kümeleri veya sınırlı bellek kaynakları olan ortamlar için önemlidir
*   **Hızlı Ön Ek Aramaları:** Bir stringi'nin belirli bir ön eke sahip olup olmadığını veya belirli bir ön ekle başlayan tüm stringleri bulmak için çok etkilidir. Otomatik tamamlama sistemleri sözlükler ve yazım denetleyicileri gibi uygulamalarda kullanışlıdır.
*   **IP Yönlendirme Tabloları:** Ağ yönlendiricileri gelen paketlerin hedefine en uygun yolu bulmak için ip adreslerinin ön eklerini eşleştirmek zorundadır atricia tree bu tür eşleştirmeleri hızlı bir şekilde yapmak için idealdir
*   **Veritabanı İndeksleme:** string tabanlı anahtarlar için veritabanı indekslerinde kullanılabilir





## Karmaşıklık Analizi

*   **Zaman Karmaşıklığı:**
    *   **Arama:** Ortalama durumda, bir anahtarın aranması O(n) zaman alır burada n aranan anahtarın uzunluğudur (bit veya karakter sayısı) En kötü durumda tüm anahtarlar çok benzerse ve ağaç dengesizleşirse bu karmaşıklık artabilir ancak pratikte genellikle anahtar uzunluğuyla orantılıdır.
    *   **Ekleme:** Arama işlemine benzer şekilde, ortalama O(n) zaman alır.
    *   **Silme:** Silme işlemi de genellikle O(n) zaman karmaşıklığına sahiptir ancak düğümlerin birleştirilmesi veya yeniden düzenlenmesi gerekebilir

*   **Zaman Karmaşıklığı:**
    *   Patricia Tree'nin en büyük avantajlarından biri zaman verimliliğidir. Standart bir tree'de N anahtar ve ortalama L uzunluğu için O(N*L*Σ) (Σ alfabe boyutu) olabilecekken Patricia Tree'de düğüm sayısı genellikle anahtar sayısıyla (N) orantılıdır yani O(N) düğüm olur. Her düğüm sabit miktarda bilgi  tutar. Bu özellikle uzun ortak ön eklere sahip seyrek veri kümelerinde önemli bir tasarruf sağlar

## Algoritmanın Adımları

1.  **Başlangıç:** Kök düğümden başlanır.
2.  **Boş Ağaç Durumu:** Eğer ağaç boşsa yeni anahtar kök olarak eklenir.
3.  **Arama/Ekleme Yolu Takibi:**
    *   Mevcut düğümde saklanan ayrım noktası kullanılır.
    *   Eklenecek/aranacak anahtarın bu indeksteki biti kontrol edilir.
    *   Bit değerine göre (0 veya 1) ilgili çocuğa doğru ilerlenir.
4.  **Farklılaşma Noktası Bulma:**
    *   Arama sırasında ilerlenen yol boyunca anahtarla eşleşme kontrol edilir. Eğer bir yaprak düğüme ulaşılırsa ve yapraktaki anahtar aranan anahtarla eşleşiyorsa anahtar bulunmuştur
    *   Ekleme sırasında yeni anahtarın mevcut bir anahtarla farklılaştığı ilk bit pozisyonu bulunur. Bu pozisyon yeni bir iç düğümün oluşturulacağı ve dallanmanın yapılacağı yerdir
5.  **Düğüm Ekleme/Güncelleme:**
    *   Eğer ilerlenen yol bir yaprak düğüme ulaşıyorsa ve bu yapraktaki anahtar yeni eklenecek anahtarla aynı değilse bu iki anahtarın farklılaştığı ilk bit bulunur bu bit pozisyonunu temsil eden yeni bir iç düğüm oluşturulur eski yaprak düğüm ve yeni anahtarı temsil eden yeni bir yaprak düğüm bu yeni iç düğümün çocukları olur
    *   eğer ilerleme sırasında bir iç düğüme gelinirse ve bu düğümdeki bit indeksi, yeni anahtarın mevcut yoldan ayrıldığı noktadan daha küçükse yola devam edilir
    *   eğer iç düğümdeki bit indeksi ayrılma noktasından büyükse veya eşitse bu durum yeni bir dallanma noktası oluşturulması gerektiğini gösterir. Yeni bir iç düğüm, ayrılma bitini temsil edecek şekilde araya eklenir
6.  **Geriye Doğru Bağlantılar :** Patricia tree'lerde bazen arama ve silme işlemlerini kolaylaştırmak için yaprak düğümlerden atalarına doğru geriye doğru bağlantılar (uplinks veya back-pointers) tutulur. Bu, özellikle bir anahtarın tam olarak nerede farklılaştığını bulmak için önemlidir.


## Kullanıldığı Yerlere Örnekler


*   **Ağ Yönlendirme :** Yönlendiriciler ip adreslerini verimli bir şekilde eşleştirmek ve paketleri doğru hedefe yönlendirmek için Patricia tree (veya benzeri radix tree varyantları) kullanır Özellikle longest prefix match için idealdir.
*   **Sözlükler ve Otomatik Tamamlama:** bir kelime dağarcığını saklamak ve kullanıcı yazarken kelime önerileri sunmak için kullanılır Örneğin, bir mobil klavyedeki kelime tahmin özelliği,
*   **Yazım Denetleyicileri:** bir kelimenin sözlükte olup olmadığını hızlıca kontrol etmek için kullanılabilir
*   **Veritabanı İndeksleme:** Özellikle metin tabanlı veya string anahtarlarına sahip veritabanlarında indeksleme yapısını optimize etmek için kullanılır
*   **Biyoinformatik:** dna dizileri gibi uzun biyolojik dizilerin analizi ve karşılaştırılmasında kullanılabilir.
*   **Veri Sıkıştırma Algoritmaları:** Bazı sıkıştırma tekniklerinde tekrarlayan string kalıplarını bulmak ve verimli bir şekilde temsil etmek için temel oluştrabilir.
*   **Sembol Tabloları:** Derleyicilerde ve yorumlayıcılarda sembollerin (değişken isimleri, fonksiyon isimleri vb) yönetimi için kullanılabilir.
*   **Blokzincir (Blockchain) Teknolojisi:** Eth gibi bazı blokzincir platformlarında, hesap durumlarını ve depolama alanını verimli bir şekilde temsil etmek ve doğrulamak için Merkle Patricia tree adı verilen bir çeşidi kullanılır. Bu yapı verinin bütünlüğünü kriptografik olarak kanıtlamayı sağlar.

## Avantajları

*   **Zaman Verimliliği:** En önemli avantajıdır tek çocuklu düğüm zincirlerini ortadan kaldırarak standart tree'lere göre önemli ölçüde daha az bellek kullanır.
*   **Hızlı Arama, Ekleme ve Silme:** Anahtar uzunluğuyla orantılı (genellikle O(n)) işlem süreleri sunar
*   **Ön Ek Tabanlı İşlemlerde Etkinlik:** Belirli bir ön eke sahip tüm anahtarları bulma veya bir anahtarın belirli bir ön ekle başlayıp başlamadığını kontrol etme gibi işlemler için çok verimlidir.
*   **Sıralı Erişim:** ağacın sıralı  dolaşılmasıyla anahtarlar alfabetik sırada elde edilebilir
*   **Dinamik Yapı:** anahtarlar eklendikçe veya silindikçe yapı dinamik olarak büyüyüp küçülebilir.

## Dezavantajları

*   **Karmaşık Implementasyon:** standart tree'lere veya basit arama ağaçlarına göre implementasyonu daha karmaşık olabilir özellikle silme işlemi ve düğüm birleştirme mantığı dikkat gerektirir.
*   **En Kötü Durum Performansı:** Aanahtarlar çok benzerse ve yapı dengesizleşirse (örneğin tüm anahtarlar aynı uzun ön eke sahipse ve sonraki bitlerde farklılaşıyorsa) performans düşebilir ve yapı bir bağlı listeye benzeyebilir..
*   **Bit Düzeyinde İşlemler:** Genellikle bit düzeyinde çalıştığı için karakter tabanlı uygulamalarda ek dönüşüm veya dikkatli implementasyon gerektirebilir.
*   **Silme İşleminin Zorluğu:** Bir düğüm silindiğinde alt ağaçların yeniden düzenlenmesi veya üst düğümlerle birleştirilmesi gerekebilir buda silme işlemini ekleme ve aramaya göre biraz daha karmaşık hale getirebilir




