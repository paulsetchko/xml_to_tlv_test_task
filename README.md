# XML to TLV parser test task

## Task description
Write a program in "C" which should take as an input "XML" file (not nested, primitive) and convert it into a binary encoded "TLV" file (not nested).

The tag of each XML node shows the type of data. There are two types of data allowed: numeric or text.
It is allowed to use any "XML" parser. 

Input file example:

<START>
                <text>string 1</text>
                <text>string 2</text>
                <text>string 3</text>
                <numeric>205011</numeric>
                <numeric>7</numeric>
</START>

Output:
                TLV File

## Trivia
TLV file is a binary file, where the data is located via the following scheme:
```
   A0 D0 00 00 0A 01 02 03 04 05 06 07 08 09 0A 
  +-----+     +-+ +---------------------------+
     |         |              |
    type    length          value
```
Both type and length have the size of four bytes. The endianess is not specified.

## Prerequisites
The tool was tested on Linux Mint 20.3, but probably any modern deb-based Linux distributive will do just fine.
Run the following command to install the packets required to compile the application:
```
# apt-get install build-essential libxml2-dev
```

## Compilation
To compile the application, run the following command, while the active directory is the repository's root:
```
make
```

## Running the app
The application requires the input xml filename. Its output is the tlv file which the tool produces would be located in the repository root directory under the name of "output.tlv".
The app also produces a small debugging log. It prints out the byte length of the output tlv file. The test input file contains five data fields, with their type and length information taking the size of 5*2*4 bytes, and there are 31 data chars those xml fields contain, so the output the tool would produce for the standard input file from the repository would be 71.
Here's an example on how to run the application with an input xml as a parameter:
```
$ ./xml_to_tlv input.xml
```

## Running the application in Docker
It is also possible to execute the application using the Docker container.
To build the container, run the following command:
```
docker build -t xml_to_tlv:latest .
```
To run the code, execute the following line:
```
docker run -i -v $(pwd):/mnt -a stdout xml_to_tlv:latest
```
The output tlv file will be located in the same woking directory.

