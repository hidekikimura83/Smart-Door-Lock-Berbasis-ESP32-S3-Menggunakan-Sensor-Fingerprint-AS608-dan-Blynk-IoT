Smart Door Lock merupakan sistem keamanan pintu berbasis ESP32-S3 yang memanfaatkan sensor sidik jari AS608 sebagai metode autentikasi utama serta terintegrasi dengan platform Blynk IoT untuk pemantauan dan pengendalian secara real-time. Sistem ini dirancang untuk meningkatkan keamanan akses dengan hanya mengizinkan pengguna yang sidik jarinya telah terdaftar membuka pintu.

ESP32-S3 berfungsi sebagai pusat pengendali yang menangani komunikasi dengan sensor fingerprint, koneksi WiFi, serta layanan Blynk Cloud. Ketika sidik jari berhasil dikenali, ESP32 akan mengaktifkan relay door lock sehingga pintu terbuka selama beberapa detik sebelum kembali terkunci secara otomatis. Sebaliknya, apabila sidik jari tidak dikenali, sistem akan menolak akses dan memberikan notifikasi status melalui aplikasi Blynk.

Selain proses autentikasi, sistem juga menyediakan fitur enrollment fingerprint yang memungkinkan pengguna menambahkan sidik jari baru secara langsung melalui aplikasi Blynk tanpa perlu memodifikasi program. Pengguna juga dapat membuka pintu dari jarak jauh menggunakan tombol virtual pada aplikasi Blynk apabila diperlukan.

Untuk menjaga keandalan sistem, program dilengkapi dengan mekanisme auto reconnect terhadap jaringan WiFi dan Blynk sehingga perangkat tetap dapat beroperasi secara stabil ketika terjadi gangguan koneksi. Proses pemindaian sidik jari dilakukan secara periodik menggunakan BlynkTimer, sehingga sistem mampu merespons autentikasi dengan cepat tanpa menghambat komunikasi dengan server IoT.

Fitur Utama
🔐 Autentikasi menggunakan sensor fingerprint AS608.
📲 Monitoring status akses melalui aplikasi Blynk.
➕ Penambahan (enrollment) sidik jari melalui Blynk.
🚪 Kontrol door lock menggunakan relay.
🌐 Monitoring dan kontrol jarak jauh melalui WiFi.
🔄 Auto reconnect WiFi dan Blynk.
⚡ Berbasis ESP32-S3 dengan respons cepat dan konsumsi daya yang efisien.

Sistem ini cocok diterapkan sebagai solusi akses pintu pintar (Smart Door Lock) untuk rumah, laboratorium, ruang kantor, maupun area yang memerlukan sistem keamanan berbasis biometrik dengan kemampuan monitoring melalui Internet of Things (IoT).
