<!-- use ctrl+shift+v to open preview -->

# MunchLex
comments from the original author: 
" A simple HTML Lexer/Parser to wrap my head around lexers and parsers, the foundations of a compiler/interpreter. Since I love webscraping thought I'd give it a try! "

## Introduction and Project Idea
### Multi-Threaded Web Scraper in C

Munchlex is a multi-threaded web scraper written in C that resolves around the idea of a lexer/parser. 
The origin of this project started when the need to further enhance the performance of a python based web scraper was required.
originally Python based web scrapers though efficient, were only sequential in nature. This means that the page 
was parsed line by line which was time consuming. Hence, Munchlex and the idea of a multi-threaded web scraper was born.

## Munchlex: Overview
the multi-threaded web scraper is designed to take advantage of concurrent execution by utilizing multiple threads. 
and hence a departure from the traditional sequential web scrapers written in languages like Python. the use 
of multiple threads aims to enhance the speed and efficiency of the web scraper. making it capable to handle the large 
scale data extraction and processing 

## Features
- Multi-threaded: harnesses the power of parallel processing capabilities of multiple threads to scrape data more efficently 
and reduce the time take to scrape the data
- Fast: the multi-threaded web scraper is designed to be fast and efficient.
- performance optimization: the scraper addresses the limitations of sequential web scrapers writtent in interpreted langauges, ensurign a fastre and more efficient data extraction process
- Scalability: thanks to multi-threading, the scraper is capable of handling large scale data extraction and processing easily and more efficiently

## How to use Munchlex
This section contains steps that one can use to get there own copy of Munchlex
- firstly, fork this repository using the fork button on the top right corner of the page to get your own copy of the repository. This is to ensure that you can actively experiment with the code of the web scraper

- secondly, once you have made the fork, you can clone the repository to your local machine using the following command:
```bash
git clone <paste URL of the forked repo here>
```

- thirdly, once you have cloned the repository, you can navigate to the directory of the repository and run the following command to compile the code:
```bash
make all
```
This will create the executable file by compiling and linking the project. we can then enter the test dir and run the shell script in there to test the web scraper.
 * **Note:** Please note that the web scraper is not yet ready and tested for windows systems natively. The use of a Linux based system is recommended.
 * **Note:** To run the scraper on a windows system, you can use the windows subsystem for linux (WSL2) to run the scraper.

## Working of the Project
### Basic idea of the working 
The web scraper works by using multiple threads to scrape the data from the web pages. the function 'munchLex' processes each line fo the input file, tokenizes it and then constructs a tree of tokens which represents the document structure. the resulting tree is also printed to the log file. The function performs lexcial analysis fo the page. 

### In detail working
- when the user begins the execution. the main drive program 'main.c' orchestrates the scraping process using a thread pool.
- the main parses command-line arguments to gather information about the number of threads, files to scrape, and optional flags like "Daemon" mode (Still in development).
- the creation of the thread pool then takes place and a thread pool with specified number of threads to parallelize the process is created.
- for each file, a thread from the thread pool is assigend to execute the 'munchLex' function. This function is main parser and lexor of the scraper. the functions performs lexical analysis of the page and tokenizes the input file. ending with the construction of a tree structure for representation of the document.
- the 'lexer' function then identifies tokens such as tags and text, and a tree structure is generated to represent the hierarchical structure of the document. the tree structure is also stored in a log file.
- **NOTE:** it is recommend for the user to run the scraper to understand the working of the scraper in more detail. And how does the tree structure is generated and how the lexical analysis is performed.

## Future Work
- The scraper is still in development and there are many features that are still to be implemented.
- Daemon mode is still in development and will be implemented in the future.
- The scraper is yet to be tested on windows systems and will be tested in the future to ensure a smooth eperience for windows users.

## Conclusion
The multi-threaded web scraper is designed to be fast and efficient. It is capable of handling large scale data extraction and processing easily and more efficiently. 

### Proudly brought to you by the Munchlex team and the open source community ❤️