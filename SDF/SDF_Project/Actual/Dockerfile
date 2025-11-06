FROM openjdk:17-slim

RUN apt-get update && apt-get install -y python3 python3-pip ant && pip install jpype1 && apt-get clean

WORKDIR /Project

COPY . .

RUN ant

CMD ["echo", "Succesfuly built docker container"]