FROM gcc:11

WORKDIR /app

COPY . /app

RUN apt-get update

RUN ls -l /app/testcases

RUN echo "Listing the files in the container:" && ls -R /app

RUN make -v && make test -v