import json
import math

A1 = '{"name": "A1", "x": 0, "y": 0, "front": "A2", "back": "null", "left": "null", "right": "B1"}'

A2 = '{"name": "A2", "x": 0, "y": 1, "front": "A3", "back": "A1", "left": "null", "right": "B2"}'
	
A3 = '{"name": "A3", "x": 0, "y": 2, "front": "null", "back": "A2", "left": "null", "right": "B3"}'
	
B1 = '{"name": "B1", "x": 1, "y": 0, "front": "B2", "back": "null", "left": "A1", "right": "null"}'
	
B2 = '{"name": "B2", "x": 1, "y": 1, "front": "B3", "back": "B1", "left": "A1", "right": "C2"}'
	
B3 = '{"name": "B3", "x": 1, "y": 2, "front": "B4", "back": "B2", "left": "A3", "right": "null"}'
	
B4 = '{"name": "B4", "x": 1, "y": 3, "front": "null", "back": "B3", "left": "null", "right": "null"}'

C1 = '{"name": "C1", "x": 2, "y": 0, "front": "C2", "back": "null", "left": "B1", "right": "D1"}'
	
C2 = '{"name": "C2", "x": 2, "y": 1, "front": "C3", "back": "C1", "left": "B2", "right": "D2"}'

C3 = '{"name": "C3", "x": 2, "y": 2, "front": "null", "back": "C2", "left": "B3", "right": "D3"}'
	
D1 = '{"name": "D1", "x": 3, "y": 0, "front": "D2", "back": "null", "left": "null", "right": "null"}'
	
D2 = '{"name": "D2", "x": 3, "y": 1, "front": "D3", "back": "D1", "left": "C2", "right": "null"}'
	
D3 = '{"name": "D3", "x": 3, "y": 2, "front": "null", "back": "D2", "left": "null", "right": "null"}'

Box1 = '{"name": "Box1", "left": "B3", "right": "C3"}'

start = json.loads(A1)
aisle1 = json.loads(C3)
aisle2 = json.loads(B3)
goal = json.loads(Box1)

def distancex(begin, end):
	beginx = begin['x']
	endx = end['x']

	finalx = endx - beginx

	return finalx

def distancey(begin, end):
	beginy = begin['y']
	endy = end['y']

	finaly = endy - beginy

	return finaly

def distance_test(begin, end1, end2):
	path1 = math.sqrt(distancex(begin, end1) ** 2 + distancey(begin, end1) ** 2)
	path2 = math.sqrt(distancex(begin, end2) ** 2 + distancey(begin, end2) ** 2)

	if(path1 < path2):
		return end1
	else:
		return end2

class robot():
	x = 0;
	y = 0;

class final_distance():
	x = 0
	y = 0

path = []

#final_distance.x = distancex(start, destination)
#final_distance.y = distancey(start, destination)

final_distance.x = distancex(start, aisle1)
final_distance.y = distancey(start, aisle1)

while(robot.x != final_distance.x and robot.y != final_distance.y):
	while(robot.x != final_distance.x):
		if(final_distance.x > robot.x):
			robot.x += 1
			path.append("right")
		else:
			robot.x -= 1
			path.append("left")
		print('Robot:', robot.x, robot.y);
	while(robot.y != final_distance.y):
		if(final_distance.y > robot.y):
			robot.y += 1;
			path.append("up")
		else:
			robot.x += 1;
			path.append("down")
		print('Robot:', robot.x, robot.y);
	for x in path:
		print("Path taken: ", x)
	path.reverse()

for x in path:
	if(x == "left"):
		robot.x += 1
		print('Path taken: right')
	elif(x == "right"):
		robot.x -= 1
		print('Path taken: left')
	elif(x == "up"):
		robot.y -= 1
		print('Path taken: down')
	elif(x == "down"):
		robot.y += 1
		print('Path taken: up')
	print('Robot', robot.x, robot.y)