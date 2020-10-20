# Kemu

Have you learned pci device?

## writeup

Is this familiar？In GeekPwn2020,it's 0 sloved so I push it again.    XD
There is "-device nvme" in The problem description. But the actually changed file is msix.c(sorry for that,I wanted to give a hint).
The patch is in `source`,it's easy if you read the patch.The msix is just a pci device with nvme,use the region which nvme malloc.Then it's your show time.
(🐦🐦🐦🐦🐦🐦🐦🐦🐦🐦🐦
