#!/ Apt/bash

if [ "$EUID" -ne 0 ]; then 
  echo "Silakan jalankan skrip ini dengan sudo"
  exit
fi

USER="cakru18"
PASS="sekuro18gogogo"

echo "Membuat user baru: $USER..."

adduser --disabled-password --gecos "" $USER

echo "$USER:$PASS" | chpasswd

usermod -aG sudo $USER

echo "Selesai! User $USER telah dibuat dengan akses sudo."
