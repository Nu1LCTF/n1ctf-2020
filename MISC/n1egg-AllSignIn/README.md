# n1egg-AllSignIn

flags = misc_signin_flag + web_signin_flag + pwn_signin_flag + re_oflo_flag + crypto_vss_flag
flag = "n1egg{" + MD5.new(flags.encode()).hexdigest() + "}"
print(flag)