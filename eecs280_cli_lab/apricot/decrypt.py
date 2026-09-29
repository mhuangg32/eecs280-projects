
try:
  with open("secret.txt", "r") as file:
    content = file.read()
    for i in range(9, len(content), 10):
      print(content[i], end="")
    print()

except FileNotFoundError:
    print(f"Uh oh... I can't find secret.txt. Make sure it's in the same directory as decrypt.py.")
