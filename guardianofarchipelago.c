#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define REDEEM 3
#define TOTAL_QUESTION 30
#define HARD_QUESTION 5
#define QUESTIONS_TO_SHOW 10

#define RANK_BRONZE 0
#define RANK_PLATINUM 1
#define RANK_CHAMPS 2
#define RANK_PREMASTER 3
#define RANK_MASTER 4


typedef struct {
    char name[50];
    int point;
    int health_point;
    int hint;
    int rank;
    int right_answers;
} Player;

typedef struct {
    char question[255];
    char answer[50];
    char hints[100];
    int used_question;
} Question;

typedef struct {
    char names[50];
    char description[100];
    int price;
} Redeem;

Player player = {"", 0, 3, 3, 0, 0};
Question *questions;

int total_questions = 0;
int questions_to_show = QUESTIONS_TO_SHOW;

int double_next = 0;
int gained;
int is_hard;
int n = 1;

void tampilkanSelamatDatang(); 
void startGame();
void easyQuestion();
void hardQuestion();
void playerLogin();
void mainMenu();
void updateRank();
void displayRank(); 
void listRedeem();
void saveGame();
int levelChoice();
void menuIfPlayerDead();
void showLeaderboard();
const char* userRank(void);


// Start Game
void startGame(){
    char user_answer[100];
    char correct_answer[100];
    int question_answered = 0;
    int questions_shown = 0;
    int used_questions_count = 0;

    // untuk mereset semua pertanyaan ke belum digunakan
    for (int i = 0; i < total_questions; i++) {
        questions[i].used_question = 0;
    }

    getchar();
    
    for(int i = 0; i < questions_to_show; i++){
        int random_index;
        int attempts = 0;
        
        if (used_questions_count == total_questions) {
            for(int j = 0; j < total_questions; j++) {
                questions[j].used_question = 0;
            }
            used_questions_count = 0;
        }
        // Memilih pertanyaan acak yang belum digunakan
        do {
            random_index = rand() % total_questions;
            attempts++;
            if(attempts > total_questions * 2) {
                for(int j = 0; j < total_questions; j++) {
                    questions[j].used_question = 0;
                }
                used_questions_count = 0;
                attempts = 0;
            }
        } while(questions[random_index].used_question == 1);

        // tandai pertanyaan yang sudah digunakan
        questions[random_index].used_question = 1;
        used_questions_count++;
        question_answered++;
        
        // Cek nyawa player
        if(player.health_point <= 0){
            printf("GAME OVER! Nyawa kamu habis.\n");
            printf("Skor akhir: %d\n", player.point);
            return;
        }
        while(1){
            printf("Pertanyaan %d/%d\n", i+1, questions_to_show);
            printf("%s\n", questions[random_index].question);
            printf("Jawab (input y untuk melihat hint): ");
            fgets(user_answer, sizeof(user_answer), stdin);
            user_answer[strcspn(user_answer, "\n")] = 0;

            for(int i = 0; user_answer[i]; i++) {
                user_answer[i] = tolower(user_answer[i]);
            }

            strcpy(correct_answer, questions[random_index].answer);

            for(int j = 0; correct_answer[j]; j++) {
                correct_answer[j] = tolower(correct_answer[j]);
            }

            // Cek hint
            if(strcmp(user_answer, "y") == 0){
                if(player.hint > 0){
                    printf("%s\n", questions[random_index].hints);
                    player.hint--;
                    printf("Sisa kesempatan hints %d\n", player.hint);
                    continue;
                } else{
                    printf("Maaf Hint Kamu Habis!\n\n");
                    continue;
                }
            }  
            
            // Agar input "kapuas (tanpa "sungai")" atau "sungai kapuas" terhitung benar
            if (strcmp(questions[random_index].answer, "Sungai Kapuas") == 0) {
                if (strcmp(user_answer, "kapuas") == 0 || strcmp(user_answer, "sungai kapuas") == 0) {
                    printf("Jawaban Benar\n");
                    player.right_answers += 1;

                    gained = 20;
                    if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! "); }
                    player.point += gained;
                    printf("Skor Anda Sekarang: %d\n\n", player.point);
                    break;
                } else {
                    printf("Jawaban Salah\n");
                    printf("Jawaban yang benar : Sungai Kapuas\n");
                    player.health_point -= 1;
                    printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);
                    break;
                }
            }
            // Agar input "toba (tanpa "danau")" atau "danau toba" terhitung benar
            if (strcmp(questions[random_index].answer, "Danau Toba") == 0) {
                if (strcmp(user_answer, "toba") == 0 || strcmp(user_answer, "danau toba") == 0) {
                    // dianggap benar
                    printf("Jawaban Benar\n");
                    player.right_answers += 1;

                    gained = 20;
                    if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! "); }
                    player.point += gained;
                    printf("Skor Anda Sekarang: %d\n\n", player.point);
                    break;
                } else {
                    printf("Jawaban Salah\n");
                    printf("Jawaban yang benar : Danau Toba\n");
                    player.health_point -= 1;
                    printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);
                    break;
                }
            }
            // Agar input "towuti (tanpa "danau")" atau "danau towuti" terhitung benar
            if (strcmp(questions[random_index].answer, "Danau Towuti") == 0) {
                if (strcmp(user_answer, "towuti") == 0 || strcmp(user_answer, "danau towuti") == 0) {
                    // dianggap benar
                    printf("Jawaban Benar\n");
                    player.right_answers += 1;

                    gained = 20;
                    if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! "); }
                    player.point += gained;
                    printf("Skor Anda Sekarang: %d\n\n", player.point);
                    break;
                } else {
                    printf("Jawaban Salah\n");
                    printf("Jawaban yang benar : Danau Towuti\n");
                    player.health_point -= 1;
                    printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);
                    break;
                }
            }
            // Agar input "madura (tanpa "suku")" atau "suku madura" terhitung benar
            if (strcmp(questions[random_index].answer, "Suku Madura") == 0) {
                if (strcmp(user_answer, "madura") == 0 || strcmp(user_answer, "suku madura") == 0) {
                    // dianggap benar
                    printf("Jawaban Benar\n");
                    player.right_answers += 1;

                    gained = 20;
                    if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! "); }
                    player.point += gained;
                    printf("Skor Anda Sekarang: %d\n\n", player.point);
                    break;
                } else {
                    printf("Jawaban Salah\n");
                    printf("Jawaban yang benar : Suku Madura\n");
                    player.health_point -= 1;
                    printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);
                    break;
                }
            }
            if (strcmp(questions[random_index].answer, "Selat Bali") == 0) {
                if (strcmp(user_answer, "bali") == 0 || strcmp(user_answer, "selat bali") == 0) {
                    // dianggap benar
                    printf("Jawaban Benar\n");
                    player.right_answers += 1;

                    gained = 20;
                    if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! "); }
                    player.point += gained;
                    printf("Skor Anda Sekarang: %d\n\n", player.point);
                    break;
                } else {
                    printf("Jawaban Salah\n");
                    printf("Jawaban yang benar : Selat Bali\n");
                    player.health_point -= 1;
                    printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);
                    break;
                }
            }
            if (strcmp(questions[random_index].answer, "Borobudur") == 0) {
                if (strcmp(user_answer, "candi borobudur") == 0 || strcmp(user_answer, "borobudur") == 0) {
                    // dianggap benar
                    printf("Jawaban Benar\n");
                    player.right_answers += 1;

                    gained = 20;
                    if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! "); }
                    player.point += gained;
                    printf("Skor Anda Sekarang: %d\n\n", player.point);
                    break;
                } else {
                    printf("Jawaban Salah\n");
                    printf("Jawaban yang benar : Candi Borobudur\n");
                    player.health_point -= 1;
                    printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);
                    break;
                }
            }

        
            // Cek jawaban
            if(strcmp(user_answer, correct_answer) == 0) {
                printf("Jawaban Benar\n");
                player.right_answers += 1;
                if(is_hard){
                    gained = 20;
                } else{
                    gained = 10;
                }
                if (double_next != 0) { gained *= 2; double_next--; printf("DOUBLE POIN! ");}
                player.point += gained;
                printf("Skor Anda Sekarang: %d\n\n", player.point);
                break;
            } else {
                printf("Jawaban Salah\n");
                printf("Jawaban yang benar : %s\n", questions[random_index].answer);
                player.health_point -= 1;
                printf("Nyawa berkurang. Sisa %d\n\n", player.health_point);

                break;
            }
        }
    }    
    saveGame();
    printf("\nSELAMAT! Kamu menyelesaikan semua soal.\n");
    printf("Skor akhir: %d\n\n", player.point);      
}

// Menu Jika Nyawa Habis
void menuIfPlayerDead(){
    if(player.health_point <= 0){
        do {
            int menu_choice;
            printf("Silahkan Pilih Menu yang Tersedia\n");
            printf("1. Lihat Rank\n");
            printf("2. Redeem Untuk Beli Nyawa\n");
            printf("3. Leaderboard\n");
            printf("4. Save Game\n");
            printf("5. Keluar\n");
            printf("Pilih : ");
            if (scanf("%d", &menu_choice) != 1) {
                printf("Input tidak valid! Harus angka.\n");

                // Buang semua karakter sisa di buffer
                while (getchar() != '\n');

                continue;
            }
            
            switch(menu_choice) {
                case 1:
                    displayRank();
                    break;
                case 2:
                    listRedeem();
                    if(player.health_point > 0){
                        return;
                    }
                    break;
                case 3:
                    showLeaderboard();
                    break;
                case 4:
                    saveGame();
                    break;
                case 5:
                    exit(0);
                default:
                    printf("Input Tidak Valid! Pilih 1-5\n");
                    menuIfPlayerDead();
                    return;
            }
        } while(1);
    }
}

// Soal Mudah
void easyQuestion(){
    is_hard = 0;
    total_questions = 38;
    questions_to_show = QUESTIONS_TO_SHOW;

    if(questions != NULL) {
        free(questions);
    }
    
    // Alokasi memori untuk array soal
    questions = (Question *) malloc(sizeof(Question) * 38);

    for(int i = 0; i < total_questions; i++) {
        questions[i].used_question = 0;
    }
        strcpy(questions[0].question, "Nama Ibukota dari Jawa Barat?");
        strcpy(questions[0].answer, "Bandung");
        strcpy(questions[0].hints, "B _ _ d _ _ g");

        strcpy(questions[1].question, "Nama Ibukota dari Jawa Tengah?");
        strcpy(questions[1].answer, "Semarang");
        strcpy(questions[1].hints, "S _ _ a _ _ n _");

        strcpy(questions[2].question, "Nama Ibukota dari Jawa Timur?");
        strcpy(questions[2].answer, "Surabaya");
        strcpy(questions[2].hints, "S _ _ a _ a _ _");

        strcpy(questions[3].question, "Nama Ibukota dari Bali?");
        strcpy(questions[3].answer, "Denpasar");
        strcpy(questions[3].hints, "D _ n _ _ s _ _");

        strcpy(questions[4].question, "Nama Ibukota dari Sumatera Utara?");
        strcpy(questions[4].answer, "Medan");
        strcpy(questions[4].hints, "M _ _ _ _");

        strcpy(questions[5].question, "Nama Ibukota dari Sumatera Selatan?");
        strcpy(questions[5].answer, "Palembang");
        strcpy(questions[5].hints, "P _ _ e _ _ _ n _");

        strcpy(questions[6].question, "Nama Ibukota dari Kalimantan Barat?");
        strcpy(questions[6].answer, "Pontianak");
        strcpy(questions[6].hints, "P _ _ _ i _ n _ _");

        strcpy(questions[7].question, "Nama Ibukota dari Kalimantan Timur?");
        strcpy(questions[7].answer, "Samarinda");
        strcpy(questions[7].hints, "S _ _ _ r i _ _ _");

        strcpy(questions[8].question, "Nama Ibukota dari Sulawesi Selatan?");
        strcpy(questions[8].answer, "Makassar");
        strcpy(questions[8].hints, "M _ _ _ s _ a _");

        strcpy(questions[9].question, "Nama Ibukota dari Papua?");
        strcpy(questions[9].answer, "Jayapura");
        strcpy(questions[9].hints, "J _ _ _ p _ _ a");

        strcpy(questions[10].question, "Nama Ibukota dari Sumatera Barat?");
        strcpy(questions[10].answer, "Padang");
        strcpy(questions[10].hints, "_ _ d _ n _");

        strcpy(questions[11].question, "Nama Ibukota dari Jambi?");
        strcpy(questions[11].answer, "Jambi");
        strcpy(questions[11].hints, "J _ _ _ i");

        strcpy(questions[12].question, "Nama Ibukota dari Riau?");
        strcpy(questions[12].answer, "Pekanbaru");
        strcpy(questions[12].hints, "P _ _ a _ _ a _ u");

        strcpy(questions[13].question, "Nama Ibukota dari Banten?");
        strcpy(questions[13].answer, "Serang");
        strcpy(questions[13].hints, "S _ _ a _ g");

        strcpy(questions[14].question, "Nama Ibukota dari DKI Jakarta?");
        strcpy(questions[14].answer, "Jakarta");
        strcpy(questions[14].hints, "_ a _ a _ _ a");

        strcpy(questions[15].question, "Nama Ibukota dari Daerah Istimewa Yogyakarta?");
        strcpy(questions[15].answer, "Yogyakarta");
        strcpy(questions[15].hints, "Y _ _ _ _ _ _ _ _ a");

        strcpy(questions[16].question, "Nama Ibukota dari Kalimantan Selatan?");
        strcpy(questions[16].answer, "Banjarmasin");
        strcpy(questions[16].hints, "B _ _ _ _ r _ _ s _ _");

        strcpy(questions[17].question, "Nama Ibukota dari Nusa Tenggara Barat?");
        strcpy(questions[17].answer, "Mataram");
        strcpy(questions[17].hints, "M _ _ _ r _ _");

        strcpy(questions[18].question, "Nama Ibukota dari Nusa Tenggara Timur?");
        strcpy(questions[18].answer, "Kupang");
        strcpy(questions[18].hints, "K _ _ a _ g");

        strcpy(questions[19].question, "Nama Ibukota dari Gorontalo?");
        strcpy(questions[19].answer, "Gorontalo");
        strcpy(questions[19].hints, "G _ r _ n _ _ l _");

        strcpy(questions[20].question, "Nama Ibukota dari Sulawesi Barat?");
        strcpy(questions[20].answer, "Mamuju");
        strcpy(questions[20].hints, "M _ m _ j _");

        strcpy(questions[21].question, "Nama Ibukota dari Sulawesi Utara?");
        strcpy(questions[21].answer, "Manado");
        strcpy(questions[21].hints, "M _ _ a _ o");

        strcpy(questions[22].question, "Nama Ibukota dari Sulawesi Tenggara?");
        strcpy(questions[22].answer, "Kendari");
        strcpy(questions[22].hints, "K _ _ d _ _ i");

        strcpy(questions[23].question, "Nama Ibukota dari Maluku Utara?");
        strcpy(questions[23].answer, "Sofifi");
        strcpy(questions[23].hints, "S _ _ i _ i");

        strcpy(questions[24].question, "Nama Ibukota dari Maluku?");
        strcpy(questions[24].answer, "Ambon");
        strcpy(questions[24].hints, "A _ _ _ n");

        strcpy(questions[25].question, "Nama Ibukota dari Papua Barat?");
        strcpy(questions[25].answer, "Manokwari");
        strcpy(questions[25].hints, "M _ _ _ k _ a _ _");

        strcpy(questions[26].question, "Nama Ibukota dari Papua Tengah?");
        strcpy(questions[26].answer, "Nabire");
        strcpy(questions[26].hints, "N _ b _ _ e");

        strcpy(questions[27].question, "Nama Ibukota dari Papua Pegunungan?");
        strcpy(questions[27].answer, "Jayawijaya");
        strcpy(questions[27].hints, "J _ _ _ w _ _ a _ a");

        strcpy(questions[28].question, "Nama Ibukota dari Papua Selatan?");
        strcpy(questions[28].answer, "Merauke");
        strcpy(questions[28].hints, "_ e_ _ u _ e");

        strcpy(questions[29].question, "Nama Ibukota dari Papua Barat Daya?");
        strcpy(questions[29].answer, "Sorong");
        strcpy(questions[29].hints, "S _ r _ _ g");

        strcpy(questions[30].question, "Nama Ibukota dari Nanggroe Aceh Darussalam?");
        strcpy(questions[30].answer, "Banda Aceh");
        strcpy(questions[30].hints, "B _ _ _ a A _ _ _");

        strcpy(questions[31].question, "Nama Ibukota dari Kepulauan Riau?");
        strcpy(questions[31].answer, "Tanjung Pinang");
        strcpy(questions[31].hints, "_ a _ _ _ _ g P _ n _ n _");

        strcpy(questions[32].question, "Nama Ibukota dari Bangka Belitung?");
        strcpy(questions[32].answer, "Pangkal Pinang");
        strcpy(questions[32].hints, "_ a _ _ _ _ l P _ n _ n _");

        strcpy(questions[33].question, "Nama Ibukota dari Bengkulu?");
        strcpy(questions[33].answer, "Bengkulu");
        strcpy(questions[33].hints, "B _ _ _ _ _ _ _");

        strcpy(questions[34].question, "Nama Ibukota dari Lampung?");
        strcpy(questions[34].answer, "Bandar Lampung");
        strcpy(questions[34].hints, "_ _ _ d _ _ L _ _ _ _ _ _");

        strcpy(questions[35].question, "Nama Ibukota dari Kalimantan Tengah?");
        strcpy(questions[35].answer, "Palangka Raya");
        strcpy(questions[35].hints, "P _ _ _ _ _ k _ R _ _ _");

        strcpy(questions[36].question, "Nama Ibukota dari Kalimantan Utara?");
        strcpy(questions[36].answer, "Tanjung Selor");
        strcpy(questions[36].hints, "T _ _ _ u _ _ _ _ l _ _");
        
        strcpy(questions[37].question, "Nama Ibukota dari Sulawesi Tengah?");
        strcpy(questions[37].answer, "Palu");
        strcpy(questions[37].hints, "P _ _ _");
}

// Soal Sulit
void hardQuestion(){
    is_hard = 1;
    total_questions = 41;
    questions_to_show = QUESTIONS_TO_SHOW;

    if(questions != NULL) {
        free(questions);
    }

    // Alokasi memori untuk array soal
    questions = (Question *) malloc(sizeof(Question) * 41);

	for(int i = 0; i < total_questions; i++) {
        questions[i].used_question = 0;
    }

    strcpy(questions[0].question, "Ibukota provinsi tempat Danau Toba?");
    strcpy(questions[0].answer, "Medan");
    strcpy(questions[0].hints, "M _ _ _ _");

    strcpy(questions[1].question, "Burung endemik Papua yang terkenal?");
    strcpy(questions[1].answer, "Cendrawasih");
    strcpy(questions[1].hints, "C _ n _ r _ w _ s _ h");

    strcpy(questions[2].question, "Hewan langka dan besar di Sulawesi (malam)?");
    strcpy(questions[2].answer, "Tarsius");
    strcpy(questions[2].hints, "T _ r _ _ _ s");

    strcpy(questions[3].question, "Sungai terpanjang di Indonesia?");
    strcpy(questions[3].answer, "Sungai Kapuas");
    strcpy(questions[3].hints, "S _ n _ _ i  K _ p _ _ _");

    strcpy(questions[4].question, "Pulau tempat Komodo hidup?");
    strcpy(questions[4].answer, "Pulau Komodo");
    strcpy(questions[4].hints, "P _ l _ u  K _ m _ d _");

    strcpy(questions[5].question, "Nama gunung tertinggi di Pulau Jawa?");
    strcpy(questions[5].answer, "Semeru");
    strcpy(questions[5].hints, "S _ m _ r _");

    strcpy(questions[6].question, "Lagu daerah 'Ampar-Ampar Pisang' berasal dari?");
    strcpy(questions[6].answer, "Kalimantan Selatan");
    strcpy(questions[6].hints, "K _ l _ m _ n t _ n  S _ l _ t _ _");

    strcpy(questions[7].question, "Danau vulkanik besar di Sumatera?");
    strcpy(questions[7].answer, "Danau Toba");
    strcpy(questions[7].hints, "D _ n _ _  T _ _ a");

    strcpy(questions[8].question, "Kota yang dikenal 'Kota Kembang'?");
    strcpy(questions[8].answer, "Bandung");
    strcpy(questions[8].hints, "B _ n _ _ _ g");

    strcpy(questions[9].question, "Nama ikan lumba-lumba air tawar (Kalimantan) yang terkenal?");
    strcpy(questions[9].answer, "Pesut");
    strcpy(questions[9].hints, "P _ s _ _");

    strcpy(questions[10].question, "Pulau di Indonesia dengan populasi terbanyak?");
    strcpy(questions[10].answer, "Jawa");
    strcpy(questions[10].hints, "J _ _ _");

    strcpy(questions[11].question, "Gunung aktif di Jawa Timur yang populer?");
    strcpy(questions[11].answer, "Bromo");
    strcpy(questions[11].hints, "B _ _ _ _");

    strcpy(questions[12].question, "Ibukota provinsi yang memiliki julukan Kota Manise?");
    strcpy(questions[12].answer, "Ambon");
    strcpy(questions[12].hints, "_ _ b _ _");

    strcpy(questions[13].question, "Pulau terbesar di Indonesia?");
    strcpy(questions[13].answer, "Kalimantan");
    strcpy(questions[13].hints, "K _ l _ m _ n _ _ n");

    strcpy(questions[14].question, "Simbol daerah yang menampilkan Rumah Gadang biasanya dari?");
    strcpy(questions[14].answer, "Sumatera Barat");
    strcpy(questions[14].hints, "S _ m _ _ _ _  B _ r _ _");

    strcpy(questions[15].question, "Pulau yang memiliki karst Maros-Pangkep?");
    strcpy(questions[15].answer, "Sulawesi");
    strcpy(questions[15].hints, "S _ _ _ w _ _ _");

    strcpy(questions[16].question, "Nama pulau tempat hutan hujan luas & orangutan (Indonesia) ?");
    strcpy(questions[16].answer, "Kalimantan");
    strcpy(questions[16].hints, "K _ l _ m _ n _ _ n");

    strcpy(questions[17].question, "Nama tradisi musik/gamelan yang terkenal di Jawa Tengah?");
    strcpy(questions[17].answer, "Gamelan");
    strcpy(questions[17].hints, "G _ m _ l _ n");

    strcpy(questions[18].question, "Ibukota provinsi yang dulunya dikenal dengan Kota Lulo ?");
    strcpy(questions[18].answer, "Kendari");
    strcpy(questions[18].hints, "_ e _ d  _ _ i");

    strcpy(questions[19].question, "Danau terbesar di Sulawesi?");
    strcpy(questions[19].answer, "Danau Towuti");
    strcpy(questions[19].hints, "D _ n _ _  T _ w _ t _");
        
    strcpy(questions[20].question, "Gunung tertinggi di Indonesia?");
    strcpy(questions[20].answer, "Puncak Jaya");
    strcpy(questions[20].hints, "P _ n _ _ k  J _ _ a");

    strcpy(questions[21].question, "Suku asli yang mendiami Pulau Madura?");
    strcpy(questions[21].answer, "Suku Madura");
    strcpy(questions[21].hints, "S _ k _  M _ d _ r _");

    strcpy(questions[22].question, "Candi Buddha terbesar di Indonesia?");
    strcpy(questions[22].answer, "Borobudur");
    strcpy(questions[22].hints, "B _ r _ b _ d _ r");

    strcpy(questions[23].question, "Provinsi penghasil minyak terbesar di Indonesia?");
    strcpy(questions[23].answer, "Riau");
    strcpy(questions[23].hints, "R _ a _");

    strcpy(questions[24].question, "Tari tradisional terkenal dari Bali?");
    strcpy(questions[24].answer, "Kecak");
    strcpy(questions[24].hints, "K _ c _ k");

    strcpy(questions[25].question, "Wilayah di Indonesia yang dijuluki Bumi Cendrawasih?");
    strcpy(questions[25].answer, "Papua");
    strcpy(questions[25].hints, "P _ p _ _");

    strcpy(questions[26].question, "Laut yang memisahkan Pulau Jawa dan Kalimantan?");
    strcpy(questions[26].answer, "Laut Jawa");
    strcpy(questions[26].hints, "L _ _ t  J _ w _");

    strcpy(questions[27].question, "Alat musik tradisional khas Nusa Tenggara Timur?");
    strcpy(questions[27].answer, "Sasando");
    strcpy(questions[27].hints, "S _ s _ n d _");

    strcpy(questions[28].question, "Provinsi termuda di Indonesia (hasil pemekaran 2012)?");
    strcpy(questions[28].answer, "Kalimantan Utara");
    strcpy(questions[28].hints, "K _ l _ m _ n t _ n  U _ a r _");

    strcpy(questions[29].question, "Nama selat yang memisahkan Pulau Bali dan Pulau Jawa?");
    strcpy(questions[29].answer, "Selat Bali");
    strcpy(questions[29].hints, "S _ l _ t  B _ l _");

    strcpy(questions[30].question, "Ibukota dari provinsi letak Gunung Marapi berada?");
    strcpy(questions[30].answer, "Padang");
    strcpy(questions[30].hints, "P _ _ _ _ _");

    strcpy(questions[31].question, "Ibukota provinsi letak wisata Raja Ampat berada?");
    strcpy(questions[31].answer, "Sorong");
    strcpy(questions[31].hints, "_ o _ _ n _");

    strcpy(questions[32].question, "Ibukota provinsi letak Pulau Dewata berada?");
    strcpy(questions[32].answer, "Denpasar");
    strcpy(questions[32].hints, "D _ n _ _ _ a _");

    strcpy(questions[33].question, "Ibukota provinsi letak Pulau Komodo berada ?");
    strcpy(questions[33].answer, "Kupang");
    strcpy(questions[33].hints, "K _ _ a _ g");

    strcpy(questions[34].question, "Ibukota provinsi letak Taman Nasional Wasur berada?");
    strcpy(questions[34].answer, "Merauke");
    strcpy(questions[34].hints, "M _ _ u _ _");

    strcpy(questions[35].question, "Kota mana yang memiliki julukan Kota Garis Biru?");
    strcpy(questions[35].answer, "Manado");
    strcpy(questions[35].hints, "M _ _ _ _ _");

    strcpy(questions[36].question, "Kota mana yang memiliki sebutan Kota Daeng?");
    strcpy(questions[36].answer, "Makassar");
    strcpy(questions[36].hints, "_ _ _ a _ s _ _");

    strcpy(questions[37].question, "ibukota provinsi letak Pulau Natuna berada?");
    strcpy(questions[37].answer, "Tanjungpinang");
    strcpy(questions[37].hints, "T _ _ _ _ _ _ _ _ n _ _ _");

    strcpy(questions[38].question, "Ibukota provinsi letak Curug Cibadak berada?");
    strcpy(questions[38].answer, "Serang");
    strcpy(questions[38].hints, "S _ _ a _ g");

    strcpy(questions[39].question, "Ibukota provinsi yang dulunya dikenal dengan Kota Lulo ?");
    strcpy(questions[39].answer, "Kendari");
    strcpy(questions[39].hints, "_ e _ d  _ _ i");

    strcpy(questions[40].question, "Kota yang memiliki julukan Kota Manise?");
    strcpy(questions[40].answer, "Ambon");
    strcpy(questions[40].hints, "_ _ b _ _");
}
    
// Regist Player
void playerLogin(){
    char user_name[50];
    char choice;
    int check = 0;

    printf("Masukkan username : ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = 0;

    while (1) {
        printf("Apakah ingin memuat game sebelumnya? (y/n) : ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N' ) {
            break;
        } else {
            printf("Input tidak valid! Silahkan masukkan 'y' atau 'n'.\n");
        }
        getchar();
    }

    if(choice == 'y' || choice == 'Y'){
        FILE *f = fopen("savedata.txt", "r");
        if(f == NULL){
            printf("Tidak ada data tersimpan\n");
            printf("Memulai permainan baru\n");
            player.point = 0;
            player.health_point = 3;
            player.hint = 3;
            player.rank = 0;
            player.right_answers = 0;
            return;
        }

        char line[256];

        while(fgets(line, sizeof(line), f) != NULL){

            if(strncmp(line, "Nama: ", 6) == 0){
                sscanf(line, "Nama: %[^\n]", user_name);
                
                int point2, health_point2, hint2, right_answers2;
                char rankStr[20];
                
                fscanf(f, "Poin: %d\n", &point2);
                fscanf(f, "Nyawa: %d\n", &health_point2);
                fscanf(f, "Hint: %d\n", &hint2);
                fscanf(f, "Rank: %19[^\n]\n", rankStr); 
                fscanf(f, "Benar: %d\n", &right_answers2);
                
                if(strcmp(player.name, user_name) == 0){
                    player.point = point2;
                    player.health_point = health_point2;
                    player.hint = hint2;
                    player.right_answers = right_answers2;
                    
                    if(strcmp(rankStr, "BRONZE") == 0) player.rank = RANK_BRONZE;
                    else if(strcmp(rankStr, "PLATINUM") == 0) player.rank = RANK_PLATINUM;
                    else if(strcmp(rankStr, "CHAMPS") == 0) player.rank = RANK_CHAMPS;
                    else if(strcmp(rankStr, "PREMASTER") == 0) player.rank = RANK_PREMASTER;
                    else if(strcmp(rankStr, "MASTER") == 0) player.rank = RANK_MASTER;
                    else player.rank = RANK_BRONZE;
                    
                    check = 1;
                    break;
                }
                
                fgets(line, sizeof(line), f);
            }
        }
        fclose(f);

        if(check){
            printf("Game berhasil dimuat!\n");
            printf("Selamat datang kembali, %s!\n", player.name);
            player.health_point = 3;
            return;
        }

        printf("Data tidak ditemukan, game baru dimulai.\n");
    }

    // Game baru
    player.point = 0;
    player.health_point = 3;
    player.hint = 3;
    player.rank = 0;
    player.right_answers = 0;
}

// Save Game
void saveGame(){
    FILE *f, *temp;
    char line[256];
    char user_name[50];
    int found = 0;

    updateRank();

    // Buka file asli untuk dibaca
    f = fopen("savedata.txt", "r");
    // Buka file temporary untuk ditulis
    temp = fopen("temp_savedata.txt", "w");

    if(temp == NULL){
        printf("Gagal menyimpan permainan\n");
        if(f != NULL) fclose(f);
        return;
    }

    // Jika file savedata.txt ada, proses data lama
    if(f != NULL){
        while(fgets(line, sizeof(line), f) != NULL){
            // Cek apakah ini baris "Nama: "
            if(strncmp(line, "Nama: ", 6) == 0){
                sscanf(line, "Nama: %[^\n]", user_name);
                
                // Jika nama sama, skip data lama (akan diganti dengan data baru)
                if(strcmp(user_name, player.name) == 0){
                    found = 1;
                    // Skip 5 baris data lama
                    for(int i = 0; i < 5; i++){
                        fgets(line, sizeof(line), f);
                    }
                    // Skip separator "==================\n"
                    fgets(line, sizeof(line), f);
                    continue;
                }
            }
            // Tulis data player lain ke file temp
            fprintf(temp, "%s", line);
        }
        fclose(f);
    }

    // Tulis data player (baru atau update)
    fprintf(temp, "Nama: %s\n", player.name);
    fprintf(temp, "Poin: %d\n", player.point);
    fprintf(temp, "Nyawa: %d\n", player.health_point);
    fprintf(temp, "Hint: %d\n", player.hint);
    fprintf(temp, "Rank: %s\n", userRank());
    fprintf(temp, "Benar: %d\n", player.right_answers);
    fprintf(temp, "==================\n");

    fclose(temp);

    // Ganti file lama dengan file baru
    remove("savedata.txt");
    rename("temp_savedata.txt", "savedata.txt");

    if(found){
        printf("Data %s berhasil diperbarui!\n", player.name);
    } else {
        printf("Data %s berhasil disimpan!\n", player.name);
    }
}


// Pilih Level
int levelChoice(){
    printf("\n=====================================\n");
    printf("=             START GAME            =\n");
    printf("=====================================\n");
    printf("~ Level Kesulitan, Silahkan Pilih\n");
    printf("1. Mudah\n");
    printf("2. Sulit\n");

    int choice;
    printf("Pilih level kesulitan (masukan 0 untuk kembali ke menu utama): ");

    if (scanf("%d", &choice) != 1) {
        printf("Input tidak valid! Hanya masukan angka..\n");
        while (getchar() != '\n');
        return 0;
    }

    switch(choice){
        case 0:
            printf("Kembali ke Menu Utama..\n\n");
            return 0;

        case 1:
            easyQuestion();
            return 1;

        case 2:
            hardQuestion();
            return 1;

        default:
            printf("Pilihan tidak valid..\n");
            return 0;
    }
}

const char* userRank(void){
    switch(player.rank){
        case RANK_BRONZE:
            return "BRONZE";
        case RANK_PLATINUM:
            return "PLATINUM";
        case RANK_CHAMPS:
            return "CHAMPS";
        case RANK_PREMASTER:
            return "PREMASTER";
        case RANK_MASTER:
            return "MASTER";
		default:
			return "UNKNOWN";
    }
}

void updateRank(){
    if(player.right_answers >= 0  && player.right_answers <= 10){
            player.rank = RANK_BRONZE;
        } else if(player.right_answers >= 11  && player.right_answers <= 25){
            player.rank = RANK_PLATINUM;
        } else if(player.right_answers >= 26  && player.right_answers <= 45){
            player.rank = RANK_CHAMPS;
        } else if(player.right_answers >= 46 && player.right_answers <= 90){
            player.rank = RANK_PREMASTER;
        } else if(player.right_answers >= 91){
            player.rank = RANK_MASTER; 
    }
}

// Menampilkan Rank
void displayRank(){
    
    // Menampilkan rank berdasarkan total jawab benar
    switch(player.rank){
		case RANK_BRONZE:
			printf("\n========== RANK ANDA ==========\n");
        	printf("=         ~ BRONZE ~          =\n");
        	printf("===============================\n");
            break;
		case RANK_PLATINUM:
			printf("\n========== RANK ANDA ==========\n");
        	printf("=         ~ PLATINUM ~          =\n");
        	printf("===============================\n");
            break;
		case RANK_CHAMPS:
			printf("\n========== RANK ANDA ==========\n");
        	printf("=         ~ CHAMPS ~          =\n");
        	printf("===============================\n");
            break;
		case RANK_PREMASTER:
			printf("\n========== RANK ANDA ==========\n");
        	printf("=         ~ PREMASTER ~          =\n");
        	printf("===============================\n");
            break;
		case RANK_MASTER:
        	printf("\n========== RANK ANDA ==========\n");
        	printf("=         ~ MASTER ~          =\n");
        	printf("===============================\n");
            break;
	}
    printf("Kamu Menjawab Benar %d Soal\n\n", player.right_answers);

    printf("== Penilaian Rank Berdasarkan Soal Yang Dijawab Benar ==\n");
    printf("Bronze      : 0 -- 10 Soal Benar\n");
    printf("Platinum    : 11 -- 25 Soal Benar\n");
    printf("Champs      : 26 -- 45 Soal Benar\n");
    printf("Premaster   : 46 -- 90 Soal Benar\n");
    printf("Master      : 91++ Soal Benar\n\n");
    return;
}

// Menampilkan Redeem
void listRedeem(){
    int redeem_choice;

	printf("\n=====================================\n");
	printf("=            REDEEM STORE           =\n");
	printf("=====================================\n");
    // Menampilkan daftar hadiah yang bisa ditukar
    printf("Poin anda tersedia sebanyak: %d\n", player.point);
    printf("Daftar hadiah yang bisa ditukar:\n");
    if (player.point < 30){
        printf("Poin tidak cukup untuk menukar hadiah\n\n");
        return;
    }
    Redeem redeems[REDEEM] = {
        {"1. Hint +1 -- ", "Dapatkan 1 hint tambahan\n", 30},
        {"2. Nyawa +1 -- ", "Dapatkan 1 nyawa tambahan\n", 60},
        {"3. Double Poin untuk pertanyaan berikutnya -- ", "Poin pertanyaan berikutnya akan dikalikan 2\n", 80}
    };
    for(int i = 0; i < 3; i++){
        printf("%s %s %d\n", redeems[i].names, redeems[i].description, redeems[i].price);
    }

    // Pilih hadiah yang ingin ditukar
    printf("\nSilahkan Pilih Hadiah Yang Ingin ditukar (Masukkan 0 untuk batal) : ");
    scanf("%d", &redeem_choice);
    
    
    // Input banyaknya hadiah yang ingin ditukar
    int quantity_redeem;
    
    // Batalkan redeem jika user menginput 0
    if(redeem_choice == 0) {
        printf("Redeem dibatalkan..\n\n");
        return;
    }
    if(redeem_choice < 1 || redeem_choice > 3) {
        printf("Pilihan tidak valid!\n");
        return;
    }
    printf("Banyaknya Redeem : ");
    scanf("%d", &quantity_redeem);

    if(quantity_redeem <= 0) {
        printf("Jumlah redeem tidak valid:(\n");
        return;
    }
    


    int selected_index = redeem_choice - 1;
    int total_price = redeems[selected_index].price * quantity_redeem;
    if(player.point < total_price) {
        printf("Poin tidak cukup untuk menukar hadiah\n");
        return;
    }
   
    switch(redeem_choice) {
        case 1:
            player.point -= total_price;
            player.hint += quantity_redeem;
            printf("Jumlah hint bertambah menjadi: %d\n", player.hint);    
            break;
        case 2:
            player.point -= total_price;
            player.health_point += quantity_redeem;
            printf("Jumlah Nyawa bertambah menjadi: %d\n", player.health_point);
            break;
        case 3:  
            player.point -= total_price;
            double_next = quantity_redeem;
            printf("Poin Anda untuk pertanyaan berikutnya akan dikalikan 2!\n");
            break;
    
        default:
            printf("Pilihan tidak valid!\n");
    }
    printf("Sisa Poin : %d\n", player.point);
}

// Menu
void mainMenu(){
    do {
        printf("\n~~ Hai, %s\n", player.name);
        printf("Health Points  : %d\n", player.health_point);
        printf("Points         : %d\n", player.point);
        printf("Hint           : %d\n\n", player.hint);
        int menu_choice;
        printf("Silahkan Pilih Menu yang Tersedia\n");
        printf("1. Mulai\n");
        printf("2. Lihat Rank\n");
        printf("3. Redeem\n");
        printf("4. Leaderboard\n");
        printf("5. Save Game\n");
        printf("6. Keluar\n");
        printf("Pilih : ");
        if (scanf("%d", &menu_choice) != 1) {
                printf("Input tidak valid! Harus angka.\n");

                // Buang semua karakter sisa di buffer
                while (getchar() != '\n');

                continue;
                return;
            }
        
        switch(menu_choice) {
            case 1:
    if (levelChoice()) {
        startGame();
        if(player.health_point <= 0){
            menuIfPlayerDead();
        }
    }
    break;

            case 2:
                displayRank();
                break;
                case 3:
                listRedeem();
                break;
            case 4:
                showLeaderboard();
            break;
            case 5:
                saveGame();
            break;
            case 6:
                printf("Terima Kasih Telah Bermain Gardian of Archipelago : Indonesia Geography..\n");
                return;
            default:
                printf("Pilihan Tidak Valid\n\n");
        }
    } while(n);
}

int main(){
    srand(time(NULL));
    playerLogin();
    tampilkanSelamatDatang();
    mainMenu();
    saveGame();

    free(questions);
    return 0;
}

// Menampilkan Selamat Datang
void tampilkanSelamatDatang() {
    printf("\n=====================================================\n");
    printf("=                                                   =\n");
    printf("=                  Selamat Datang                   =\n");
    printf("=   Guardian of Archipelago : Indonesia Geography   =\n");
    printf("=                                                   =\n");
    printf("=====================================================\n");
}

void showLeaderboard() {
    saveGame();
    FILE *fileShowLeaderboard = fopen("savedata.txt", "r");
    if (fileShowLeaderboard == NULL) {
        printf("File savedata.txt tidak ditemukan.\n");
        return;
    }

    Player players[100];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fileShowLeaderboard)) {
        if (strncmp(line, "Nama: ", 6) == 0) {

            sscanf(line, "Nama: %49[^\n]", players[count].name);

            fscanf(fileShowLeaderboard, "Poin: %d\n", &players[count].point);
        	fscanf(fileShowLeaderboard, "Nyawa: %d\n", &players[count].health_point);
            fscanf(fileShowLeaderboard, "Hint: %d\n", &players[count].hint);

            /* kalau Rank disimpan STRING, pakai %*s */
            fscanf(fileShowLeaderboard, "Rank: %*s\n");

            fscanf(fileShowLeaderboard, "Benar: %d\n", &players[count].right_answers);

            count++;
        }
    }
    fclose(fileShowLeaderboard);

    if (count == 0) {
        printf("Belum ada data pemain.\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (players[j].right_answers > players[i].right_answers) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    FILE *write = fopen("leaderboard.txt", "w");
    if (write == NULL) {
        printf("Gagal membuat leaderboard.txt\n");
        return;
    }

    fprintf(write, "================= LEADERBOARD ==================\n\n");
    fprintf(write, "-----------------------------------------------\n");
    fprintf(write, "%-5s %-15s %-6s %-6s\n", "No.", "Nama", "Poin", "Soal Dijawab Benar");
    fprintf(write, "-----------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(write, "%-5d %-15s %-6d         %-6d\n",
                i + 1,
                players[i].name,
                players[i].point,
                players[i].right_answers);
    }

    fprintf(write, "\n===============================================\n");
    fclose(write);

    printf("Leaderboard berhasil dibuat (leaderboard.txt)\n");
    printf("\n=========================================\n");
    printf("=              LEADERBOARD              =\n");
    printf("=========================================\n");
    printf("%-5s %-15s %-10s %-6s\n", "No.", "Nama", "Benar", "Poin");
    printf("-----------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s %-10d %-6d\n", i + 1, players[i].name, players[i].right_answers, players[i].point);
    }

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}