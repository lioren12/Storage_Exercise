# Storage_Exercise - C programming languages
Implementation of an in memory key-value storage

Requirements:

1. Storage main properties:
	a. Key - an instance of some binary safe data.
	b. Value – an instance of some binary safe data.
	c. Eviction – timed based.
	d. Object safety must be kept, accessing the storage may happen in concurrent (lock-free/wait-free is not required).

2. Required interface:
	a. Add new element – add(key, value, deletion_point_in_time) //TODO create option to change value per key
	b. Retrieve new element – value get(key)
	c. Is exists – bool is_exists(key)

3. More:
	a. Error handling should be supported in full.
	b. What will happen when eviction interval with accessing the data? Please address.
	c. Time complexity when accessing the data – should be as fast as possible.
	d. Platform – any is fine.

4. Testing:
	a. Please provide a simple testing code proving the correctness of your code. Can be very simple, no need to use some special testing framework.
