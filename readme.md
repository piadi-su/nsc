## nsc
just a simple tcp port scanner in c


#### usage:
```text
./bin/nsc --help

usage: ./bin/nsc [group 1] [group 2] [group 3] <ip-address>
options:
[1]
-p = scan only up to port 1024
-p- = scan all ports

[2]
-v = verbose (you can see all of the scan process)
-o = see only the open port at the report

[3]
-s = slow scan (traffic less noticeable)
-f = aggressive scan (traffic more noticeable)

```
