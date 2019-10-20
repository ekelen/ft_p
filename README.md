#i ft_p

A C implementation of an FTP client/server. RFC 959 compliant(ish).

## Usage

build client and server
```sh
$ make
```

run the server
```sh
$ ./server <port>
```

run the client
```sh
$ ./client <address> <port>
```

clean up
```sh
$ make clean (remove object files)
$ or
$ make fclean (remove object and binary files)
```

client usage
```sh
ft_p » user <username>
ft_p » pass <password>
ft_p » ls
ft_p » passive
ft_p » pwd
ft_p » cd <dir>
ft_p » type <binary|image|ascii>
ft_p » get <src filename> <dest filename>
ft_p » put <src filename> <dest filename>
ft_p » quit
```

## Development

### Install a stable FTP server

`$ docker run --rm -d --name ftpd_server -p 21:21 -p 30000-30009:30000-30009 -e "ADDED_FLAGS=-d -d" -e "PUBLICHOST=localhost" -e FTP_USER_NAME=user42 -e FTP_USER_PASS=pass42 -e FTP_USER_HOME=/home/user42 stilliard/pure-ftpd:hardened`

`$ docker exec -it ftpd_server /bin/bash`

* See logs: `pureftpd> $ tail -f /var/log/messages`
* Create user: `pure-pw useradd user21 -u ftpuser -d /home/user21 -t 1024 -T 1024 -y 1 -m`
* show user details `pure-pw show user42`


### Install a stable ftp client

If the ftp client is not available on your version of MacOS, `brew install inetutils`

```sh
$ ftp -p localhost
ftp> Name: user42
ftp> Password: <password>
```

#### Example client usage

```sh
ftp> help           # show available commands
ftp> rstatus -v     # show status of server
ftp> pwd            # print working directory on remote machine
ftp> status         # show current status
ftp> get <file>     # get file from remote server
ftp> ls             # list remote files
```

#### Handy one-liners

- Kill processes listening on port `PORT`:

`lsof -i TCP:PORT | grep LISTEN | awk '{print $2}' | xargs kill -9`

- Get status of connections on PROCESS NAME:

`lsof -n -itcp | grep -w PROCESS_NAME`

## About

This project is part of the Ecole 42 cursus. The assignment PDF can be consulted in the `resources` subdirectory.

#### RFC Compliance

This project can be considered minimally RFC-compliant.


#### Testing

1. Create test files:

```sh
cd tests
gcc tricky_files.c && ./a.out
```

2. Launch server and client, each in a separate and visible terminal window.

3. See *instructions.md* for specific cases and their associated commands.