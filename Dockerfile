FROM ubuntu:jammy

WORKDIR /xml_to_tlv
COPY ./* /xml_to_tlv/
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y apt-utils build-essential libxml2-dev
RUN make
CMD ["/bin/sh", "-c", "./xml_to_tlv input.xml && cp output.tlv /mnt"]
