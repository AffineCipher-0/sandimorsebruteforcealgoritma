


// Berfungsi untuk menemukan elemen maksimum dalam array menggunakan brute force
int findMax(int arr[], int n) {
    int max = arr[0];  // Inisialisasi elemen maksimum ke elemen pertama array
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {  // Bandingkan elemen saat ini dengan elemen maksimum
            max = arr[i];  // Perbarui elemen maksimum jika elemen saat ini lebih besar
        }
    }
    return max;  // Mengembalikan elemen maksimum
}