FROM linuxmintd/mint20-amd64

RUN apt update
RUN apt install -y make
RUN apt install -y gcc

CMD ["bash"]