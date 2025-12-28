# Guardian of Archipelago : Indonesia Geography

**Guardian of Archipelago** adalah permainan kuis interaktif berbasis *Command Line Interface* (CLI) yang diprogram dengan menggunakan bahasa C. Permainan ini dirancang untuk menguji dan meningkatkan wawasan pemain mengenai geografi Indonesia, termasuk pengetahuan tentang ibu kota provinsi, pulau, danau, hingga budaya daerah.


## Deskripsi Proyek
Program ini mensimulasikan permainan cerdas cermat dengan sistem poin, nyawa (Health Points), dan tingkatan ranking. Pemain akan ditantang dengan berbagai pertanyaan seputar Indonesia. Semakin banyak jawaban benar, semakin tinggi ranking yang akan dicapai. Pemain juga dapat memanajemen poin mereka untuk membeli hint atau nyawa tambahan agar tidak *Game Over*.

## Fitur Utama
* **Dua Tingkat Kesulitan**:
    * **Mudah**: Fokus pada pengetahuan dasar seperti Ibu Kota Provinsi.
    * **Sulit**: Mencakup pengetahuan umum yang lebih luas (gunung, danau, fauna endemik, dll).
* **Sistem Akun & Save Data**: Kemajuan permainan (poin, rank, nyawa) tersimpan secara otomatis. Pemain dapat melanjutkan permainan dengan login menggunakan username yang sama.
* **Sistem Ranking**: Terdapat 5 tingkatan rank berdasarkan jumlah jawaban benar:
    1. Bronze
    2. Platinum
    3. Champs
    4. Premaster
    5. Master
* **Toko Penukaran (Redeem Store)**: Poin yang dikumpulkan dapat ditukarkan dengan :
    * Tambahan Hint (Petunjuk).
    * Tambahan Nyawa (Health Point).
    * Double Point untuk pertanyaan selanjutnya.
* **Leaderboard**: Menampilkan papan peringkat pemain berdasarkan jumlah jawaban benar tertinggi.
* **Mekanisme Permainan**:
    * Pertanyaan acak (Randomized).
    * Toleransi jawaban (case-insensitive).
    * Sistem Hint untuk membantu menjawab soal sulit.

## Cara Menjalankan Program
Pastikan Anda telah menginstal compiler C (seperti GCC) di komputer Anda.
1.  Download source code ProyekKelompok6.c
2.  Buka terminal atau command prompt di direktori folder proyek.
3.  **Kompilasi** kode sumber `ProyekKelompok6.c`:
    ```bash
    gcc ProyekKelompok6.c -o ProyekKelompok6
    ```
4.  **Jalankan** program:
    * **Windows**:
        ```bash
        ProyekKelompok6.exe
        ```
    * **Linux/Mac**:
        ```bash
        ./ProyekKelompok6
        ```
5.  Masukkan username Anda dan selamat bermain!

## Tim Pengembang
Proyek ini dikembangkan oleh:
* **Fawwaz Ajjihad**
* **Syarif Ahmad Hidayat**
* **Rangga Budi Satria**
