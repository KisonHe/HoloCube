import subprocess
import os

header_name = "wifihtml.h"
header_dir = "src"
html_filename = "WiFiPortal.html"
try:
    # 
    header_path = os.path.join(header_dir,header_name)
    ret = "#pragma once\n//GENERATED FILE DO NOT MODIFY\n"
    subprocess.call(["gzip", "-f", "-k",  html_filename]) #Must wait here
    ret = ret + subprocess.check_output(["xxd","-i",(html_filename + ".gz")]).decode("utf-8")
    ret = ret.replace("[]", "[] PROGMEM ") # inelegant but works
    ret = ret.replace("unsigned char", "const unsigned char") # inelegant but works
    html_c_file = open(header_path,"w+")
    html_c_file.write(ret)
    html_c_file.close()
    print("Done")
except Exception as e:
    print("Error {}".format(e))
