import mysql.connector



def test():
    res = []
    res.append(1)
    res.append(2)
    return res

res = test()
print(res[1])


# mydb = mysql.connector.connect(
#   host="192.168.1.214",
#   user="pi",
#   password="27122001",
#   database="doctorapp"
# )

# mycursor = mydb.cursor()

# mycursor.execute("SELECT * FROM patients where id = 1")

# myresult = mycursor.fetchone()

# print(myresult[1])

