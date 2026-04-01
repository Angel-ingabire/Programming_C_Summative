FROM debian:stable-slim

RUN apt-get update \
 && apt-get install -y build-essential libcurl4-openssl-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src
RUN make

CMD ["/src/mt_scraper", "/src/urls.txt", "/out"]
