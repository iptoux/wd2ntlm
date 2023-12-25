# wd2ntlm

Wordlist 2 'NTLM' hashes.

## How does it work?

Convert a file with words like rockyou.txt to a sqlite3/json/csv/xlsx database with words and corresponding ntlm hash.

SQLite3 is the default because it's used as a backend to store passwords on error/abort. You can select other formats on the command line by selecting with argument. It checks for dupes (shows dupes on debug output) to minimize overhead.

```bash
Output Options:
  --csv                 output file should be in csv fromat.
  --json                output file should be in JSON fromat.
  --xlsx                output file should be in Excel fromat.
```

There are also some extra features like **define how many threads** should be used, or **debug** output.

## Usage

```bash
usage: wd2ntlm [-h] [-d] -f FILE -o FILE [--csv] [--json] [--xlsx] [-t N] [-v]

options:
  -h, --help            show this help message and exit

General Options:
  -f FILE, --file FILE  the file to read and convert
  -o FILE, --out FILE   the output file to write hashes
  -t N, --threads N     how many threads should be used?
  -v, --version         show program's version number and exit

Nerd Options:
  -d, --debug           enable debug output
```

## Clone/Install

There is only one package needed, just clone repo and setup requirements.txt

```bash
git clone https://github.com/iptoux/wd2ntlm.git
cd wd2ntlm
pip install -r requirements.txt
chmod +x src/wd2ntlm.py
./wd2ntlm.py
```

## WARNING

It hasn't been tested with a large file like rockyou.txt (xxGB), testing and working with up to 200 words without problems.

### ToDo

+ cleanUp
+ refactor