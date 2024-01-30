# [R-Type](https://fr.wikipedia.org/wiki/R-Type)

## Project Description
This project of the Advanced C++ knowledge unit will introduce you to networked video game development, and will give you the opportunity to explore advanced development techniques as well as to learn good software engineering practices.

The goal is to implement a multithreaded server and a graphical client for a well-known legacy video game called [R-Type](https://fr.wikipedia.org/wiki/R-Type), using a game engine of your own design.

## Table of Contents
- [R-Type](#r-type)
  - [Project Description](#project-description)
  - [Table of Contents](#table-of-contents)
  - [Requirements](#requirements)
    - [Server](#server)
    - [Client](#client)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)

## Requirements

### Server

- The server must be multi-threaded
- The server must be able to handle more than one game at a time
- The server must be able to handle multiple
games in a row
- The server must be the referee of all games it manages.

### Client
- The client must contain anything necessary to display the game and handle player input.
- The client must use the [SFML](https://www.sfml-dev.org/).

## Installation

To install this Awesome Project, follow these steps:

```bash
git clone https://github.com/EpitechPromo2026B-CPP-500-LYN-5-2-rtype-ilhan.neuville.git
cd B-CPP-500-LYN-5-2-rtype-ilhan.neuville
yay -Syu cmake
yay -Syu sfml
```

## Usage

**Products to be delivered**
`r-type_server` `r-type_client`

**In Terminal**

```sh
./r-type_server [PORT]
```

**In another terminal**

```sh
./r-type_client
```
```
command for the client in rfc.txt file :
    spawnEntity <Type>
    moveEntity <typeID> <entityID> <height> <width>
    killEntity <typeID> <entityID>
    showEntity <typeID> <entityID> <true:false>
```

## Contributing

Antoine Fillaudeau, Tonin Guier, Ilhan Neuville et Amandine Rius

## License
Look License file
