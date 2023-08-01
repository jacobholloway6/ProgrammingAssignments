# projectzero


Programming assignment zero scans the content of the data in the folder data, once it has scanned the contents of the data folder it takes the information and creates a txt file under the folder result. There are two different functions, one is testalphabet and the other is testspecial. The first one will tell you the frequency of standard characters and the latter will provide you with the special characters. 

The functions begin with declaring the variables and then it will open the directories to read the data from. 

Next, it will validate that the directory was opened succesfully and then it will begin a while loop to process the data files. It will only do this with .txt files, once this is done it reads all the data from the files until it reaches the end of the file. During each time it needs to convert it to lowercase and then stores it in alphabet frequency. Once all this is done it will close the directory. Lastly it checks if the directory "result" is made and then it will create a file called either result or specialresult which are both .txt files. It will inform the user in terminal that a file has been succesfully made. Both files store the frequenct of the characters along with a time stamp when the file was made so that way each time the program is run it will provide the user with a new time stamp. I understand this might be redundant given that the computer provides information when it was last modified but I felt it was nice to add the ability to see it. 

Once the files have been made it will succesfully close the directories. 

There is also a function that appears to be displayed in the terminal displaying the information that was written to the results.txt files

Expected output for ./testalphabet:

a -> 2973036
b -> 556908
c -> 765864
d -> 1786752
e -> 4883076
f -> 765336
g -> 809292
h -> 2818068
i -> 2586276
j -> 35112
k -> 401412
l -> 1728276
m -> 1050852
n -> 2509320
o -> 2766192
p -> 562848
q -> 28776
r -> 2177076
s -> 2465496
t -> 3291684
u -> 1015608
v -> 276804
w -> 1085040
x -> 46860
y -> 730752
z -> 12936

Expected result for ./testspecial: 

, -> 745668
. -> 798072
: -> 15708
; -> 32340
! -> 63228



