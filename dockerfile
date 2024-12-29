FROM gcc:11

WORKDIR /usr/src/app

COPY . .

RUN apt-get update && apt-get install -y make

CMD ["make", "test"]