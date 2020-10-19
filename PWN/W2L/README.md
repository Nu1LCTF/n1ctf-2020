# W2L

Let's exploit the 2017 bug in 2020.

# Writeup

This is a challenge of Linux kernel exploitation. The bug introduced in the patch is CVE-2017-7308 which provides an overwrite primitive. It's not hard to find a public exploit for this bug. But the way to bypass the KASLR in these public exploits is ad-hoc. I was expecting to see folks can come up with a new technique to leak kernel information and thus bypass KALSR. Unfortunately, in the script running qemu, I mistakenly disabled SMAP/SMEP which was intended to be enabled. This mistake made this challenge easier because ret2usr is sufficient to exploit the vulnerability.

I would like to introduce the intended solution for this challenge with SMAP/SMEP and KASLR enabled. Since the public exploit has already demonstrated how to obtain the control-flow hijacking primitive from the overwrite primitive, I will focus on how to obtain the leak primitive from the overwrite primitive so as to leak kernel information and bypass KASLR.

In most kernels, there exist a special type of structure which contains a length fiekld controlling the size of a kernel buffer. This type of structure is really useful when there are channels to leak the content in the kernel buffer to the userland. For example, `copy_to_user` is one of the leaking channels in Linux kernel. When `copy_to_user` is invoked, if the `size` parameter is propagated from the length field and the `src` parameter is the address of a kernel buffer, the content of the kernel buffer can be read in the userland. We call this type of structures as `leakable elastic structure`. 

Leakable elastic structures can be used for overreading through enlarging its length field using the vulnerability. In this challenge, we already have the primitive overwriting the adjacent data, what we need to do is to find a `leakable elastic structure` , put it after the vulnerable object, overwrite the length field with a large value, and finally leak the kernel information through the channel. In this challenge, we use the leakable elastic structure `user_key_payload` to leak kernel base address. `user_key_payload` is very powerful because it can be allocated in many general caches. Its flexibility allows us to spray it in different caches to cater to different vulnerabilities. Please refer to [here](https://github.com/Markakd/n1ctf2020_W2L/blob/main/leak.c) to see our exploit utilizing `struct user_key_payload` to bypass KASLR.

Regarding this type of magic object, there is more to explore. (1) How many leakable elastic structures are there in different kernels? (2) Is this leaking technique general? (3) Do we need mitigation mechanism to prevent such leaking? (4) etc. To answer these questions, we researched on this leaking technique and published the results in our [paper](https://zplin.me/ELOISE.pdf).

