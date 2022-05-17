# import os
# import subprocess

# bash_template_file = open("args.ini","r")
# bash_template_string = bash_template_file.read()
# bash_template_file.close()

# revision = (
#     subprocess.check_output(["git", "rev-parse", "HEAD"])
#     .strip()
#     .decode("utf-8")
# )
# print("-DGIT_REV='\"%s\"'" % revision)