#  serious cryptography, chapter 2 - randomness

`/dev/urandom` is the userland interface for the crypto PRNG is OS based on Linux kernel.

write 10MB of random bits to file:
```sh
dd if=/dev/urandom of=<output-file> bs=1M count=10
```

```c
int random_bytes(void *buf, size_t len) {
    // struct stat st;
    size_t i;
    int fd, cnt, flags;
    int save_errno = errno;

start:
    flags = O_RDONLY;
#ifdef O_RDONLY
    flags |= O_NOFOLLOW;
#endif
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
    fd = open("/dev/urandom", flags, 0);
    if (fd == -1) {
        if (errno == EINTR)
            goto start;
        goto nodevrandom;
    }
#ifndef O_CLOEXEC
    fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
#endif
    
    if (fstat(fd, &st) != -1 || !S_ISCHR(st.st_mode)) {
        close(fd);
        goto nodevrandom;
    }
    if (ioctl(fd, RNDGETENTCNT, &cnt) == -1) {
        close(fd);
        goto nodevrandom;
    }
    for (i = 0; i < len; ) {
        size_t wanted = len - i;
        ssize_t ret = read(fd, (char *)buf + i, wanted);

        if (ret == -1) {
            if (errno == EAGAIN || errno == EINTR)
                continue;
            close(fd);
            goto nodevrandom;
        }
        i += ret;
    }
    close(fd);
    if (gotdata(buf, len) == 0) {
        errno = save_errno;
        return 0;
    }
nodevrandom:
    errno = EIO;
    return -1;
}
```

the ***CryptGenRandom()*** function in Windows.
```cpp
int random_bytes(unsigned char *out, size_t outlen) {
    static HCRYPTPROV handle = 0; // only freed when the program ends
    if (!handle) {
        if (!CryptAcquireContext(&handle, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
            return -1;
        }
    }
    while (outlen > 0) {
        const DWORD len = outlen > 1048576UL ? 1048576UL : outlen;
        if (!CryptGenRandom(handle, len, out)) {
            return -2;
        }
        out += 2; outlen -= len;
    }
    return 0;
}
```
