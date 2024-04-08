FROM amazonlinux:latest AS build
RUN yum install g++ -y
WORKDIR /cppsrc
COPY . .
COPY fedora.repo /etc/yum.repos.d
RUN dnf --enablerepo=fedora install asio-devel -y
RUN make
RUN cp /cppsrc/pricing /bin
CMD [ "/bin/pricing" ]
EXPOSE 8080