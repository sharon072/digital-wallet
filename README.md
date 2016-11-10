

The source code is implemented by C++ only and it can be used to detect fraudulent payment requests from untrusted users based on their social network.
Due to my busy schedule now, there is still optimization which haven't be finished yet. 
For example,
1. All history data in "batch-payment.csv" should be stored in some data storage before run the program. It will improve the runtime complexity obviously.
2. When checking for existence of a key in the map, instead of using "map.find(key) != map.end()", utilize the algorithm of QUICK SORT and Binary Search will improve the efficiency more and more

Finally, due to my low-performence device, I'm unable to run with the initial input files when testing Feature 2 and Feature 3, therefore, output1.txt, output2.txt and output3.txt are all based on the test input file "batch.csv" and "stream.csv."
Only output1_com.txt is the output of Feature 1 based on the initial input files. Please keep in mind.
Thanks!


##Challenge Summary

Imagine you're a data engineer at a "digital wallet" company called PayMo that allows users to easily request and make payments to other PayMo users. The team at PayMo has decided they want to implement features to prevent fraudulent payment requests from untrusted users. 

###Feature 1
When anyone makes a payment to another user, they'll be notified if they've never made a transaction with that user before.

* "unverified: You've never had a transaction with this user before. Are you sure you would like to proceed with this payment?"

###Feature 2
The PayMo team is concerned that these warnings could be annoying because there are many users who haven't had transactions, but are still in similar social networks. 

For example, User A has never had a transaction with User B, but both User A and User B have made transactions with User C, so User B is considered a "friend of a friend" for User A.

For this reason, User A and User B should be able to pay each other without triggering a warning notification since they're "2nd degree" friends. 

<img src="./images/friend-of-a-friend1.png" width="500">

To account for this, PayMo would like you to also implement this feature. When users make a payment, they'll be notified when the other user is outside of their "2nd-degree network".

* "unverified: This user is not a friend or a "friend of a friend". Are you sure you would like to proceed with this payment?"


###Feature 3
More generally, PayMo would like to extend this feature to larger social networks. Implement a feature to warn users only when they're outside the "4th degree friends network".

<img src="./images/fourth-degree-friends2.png" width="600">

In the above diagram, payments have transpired between User

* A and B 
* B and C 
* C and D 
* D and E 
* E and F

Under this feature, if User A were to pay User E, there would be no warning since they are "4th degree friends". 

However, if User A were to pay User F, a warning would be triggered as their transaction is outside of the "4th-degree friends network."

(Note that if User A were to pay User C instead, there would be no warning as they are "2nd-degree" friends and within the "4th degree network") 
