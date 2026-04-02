# Project 5 — Multi-threaded Web Scraper

This scraper uses POSIX threads and libcurl to fetch multiple URLs in parallel. Each thread writes its output to a separate file (no thread synchronization required).

Build

Dependencies: `gcc` (or compatible), `libcurl` development headers, and `pthread` support.

On Linux/macOS:

```sh
cd project5
make
```

On Windows: install MSYS2/MinGW and the `libcurl` development package (or use WSL).
Then build inside that environment (MSYS shell) with `make` or run `gcc` directly.

Docker (recommended for reproducible builds):

```sh
cd project5
docker build -t project5-scraper .
# mount current directory to capture outputs
docker run --rm -v "$PWD/out":/out project5-scraper
```

This builds and runs the scraper inside a Debian container (libcurl + pthreads available).

Usage

```sh
./mt_scraper urls.txt [output_dir]
```

- `urls.txt` — newline-separated list of URLs.
- `output_dir` — optional directory; defaults to current directory. Output files are named `output_<N>.html` or `output_<N>.err.txt` for errors.


Notes

- No mutexes are used; each thread writes to its own file.
- Basic error handling: libcurl errors and file open errors are written to per-thread `.err.txt` files.
- The program will attempt to create the output directory if it does not exist.
- Network requests use a 30s timeout per URL.
