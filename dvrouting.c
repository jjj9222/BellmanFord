#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 500

//Stuck on putting the weight into the structure


struct Edge {
	int start;
	int end;
	int weight;
};

struct Graph {
	int V;
	int E;
	struct Edge *edge;
};

void printTableHead(FILE* write, int time){
	fprintf(write, "Time %d:\n", time);
	fprintf(write, "\tDistance Table:\n");
	fprintf(write, "\t\tDistance Table for A:\n");
	fprintf(write, "\t\t--------------------\n");
	fprintf(write, "\t\tTo\t\tVia\n");
}

void bellmanford(struct Graph *g, int source, char* populate, FILE* file, char* letters){
	int i, j, u, v, w, tempVar = 0;
	int index = 0, num = 0, forvar = 0;
	int test = g->V * 8 * g->E;
	
	int totalV = g->V;
	int directV = 0;
	
	int totalE = g->E;

	int d[totalV];
	int p[totalV];
	char format1[test];
	char formattemp[test];
	char temp[5];
	int line[totalV];
	//printf("%s\n", populate);
	for(int t = 0; t < (g->V)-1; t++){
		line[t] = 1414;	
	}
	
	for (i=1; i < totalV; i++){
		d[i] = 1414;
		p[i] = 0;
	}
	int local = 0;
	fprintf(file, "\t\t");
	for(int e = 0; e < test; e++){
		memset(temp, 0, 5);
		local = 0;
		if('*' == populate[e]){
			e = test;	
		}
		else if(';' == populate[e]){
			tempVar = e+1;
			while((47 < populate[tempVar]) && (58 > populate[tempVar])){
				//found index number
				//printf("Found index number after ;\n");
				temp[local] = populate[tempVar];
				tempVar += 1;
				local += 1;
			}
			index = atoi(temp);
			directV += 1;
			fprintf(file, "\t%c", letters[index-1]);
			
		}
		else if(',' == populate[e]){
			tempVar = e+1;
			while((47 < populate[tempVar]) && (58 > populate[tempVar])){
				//found index number
				//printf("Found index number after ,\n");
				temp[local] = populate[tempVar];
				tempVar += 1;
				local += 1;
			}
			num = atoi(temp);
			//printf("Putting num into the distance array\n");
			d[index] = num;
		}
		
	}
	fprintf(file, "\n");
	//set the orgin to zero
	d[0] = 0;
	//printf("%d\n", totalE);
	memset(format1, 0, test);
	for(i = 1; i <= totalV-1; i++){
		for(j = 0; j < totalE; j++){
			//loop through each edge
			u = g->edge[j].start;
			v = g->edge[j].end;
			w = g->edge[j].weight;
			
			//formatting array below
			if(1 == i){
				format1[forvar] = 's';
				forvar += 1;
				strcpy(formattemp, format1);
				snprintf(format1, test, "%s%d",formattemp, u);
				if(u > 9){
					forvar += 1;
				}
				forvar += 1;
				format1[forvar] = 'd';
				forvar += 1;
				strcpy(formattemp, format1);
				snprintf(format1, test, "%s%d",formattemp, v);
				if(v > 9){
					forvar += 1;
				}
				forvar += 1;
				format1[forvar] = 'c';
				forvar += 1;
				strcpy(formattemp, format1);
				snprintf(format1, test, "%s%d",formattemp, w);
				if(w > 9){
					forvar += 1;	
				}
				if(w > 99){
					forvar += 1;	
				}
				forvar += 1;
				format1[forvar] = 'x';
				forvar += 1;
			}
			if (d[v] > d[u] + w){
				d[v] = d[u] + w;
				printf("%d\n", u);
				p[v] = u;
			}
			
		}
	}
	//printf("%s\n", format1);
	//need to travel through the format array to print the correct values line by line
	for(int row = 1; row < totalV; row++){
		memset(temp, 0, 5);
		local = 0;
		int holder = 0, holder2 = 0;
		//find all of the values for each row
		int Avalue = 0;
		memset(line, 0, sizeof(line));
		for(int val = 0; val < test; val++){
			if(0 == format1[val]){
				val = test;	
			}
			if('d' == format1[val]){
				holder = val;
				holder2 = val;
				holder2 += 1;
				memset(temp, 0, 5);
				local = 0;
				while((47 < format1[holder2]) && (58 > format1[holder2])){
					temp[local] = format1[holder2];
					local += 1;
					holder2 += 1;
				}
				//printf("%d compare to %d\n", atoi(temp), row);
				if(atoi(temp) == row || atoi(temp) == 0){
					//on that row ready to put into a line array
					//need to get the index to line
					int isA = atoi(temp);
					memset(temp,0,5);	
					local = 0;
					holder2 += 1;
					while((47 < format1[holder2]) && (58 > format1[holder2])){
						temp[local] = format1[holder2];
						local += 1;
						holder2 += 1;
					}
					int weight = atoi(temp);
					//printf("%d\n", weight);
					memset(temp,0,5);
					local = 0;
					holder -= 1;
					while((47 < format1[holder]) && (58 > format1[holder])){
						holder -= 1;
					}
					holder += 1;
					while((47 < format1[holder]) && (58 > format1[holder])){
						temp[local] = format1[holder];
						holder += 1;	
					}
					if(0 == isA){
						Avalue = weight;	
					}
					if(0 == isA && row == atoi(temp)){
						line[row] = weight;	
					}
					else if(0 != isA){
						line[atoi(temp)] = Avalue + weight;
						//printf("%d\n", line[atoi(temp)]);
					}
					//printf("%d ", line[atoi(temp)]);
				}
				//printf("\n");
				//printf("%c\n", format1[val+1]);
			}
			
		}
		fprintf(file, "\t\t%c\t", letters[row-1]);
		for( int l = 1; l <= directV; l++){
			if(0 == line[l]){
				fprintf(file, "--\t");	
			}
			else{
				fprintf(file, "%d\t", line[l]);
			}
		}
		fprintf(file, "\n");
		
	}
	fprintf(file,"\n\tRouting Table: \n\t\tRouting Table for A:\n\t\t--------------------\n\t\tDest\tNxtHp\n");
	for(int route = 1; route < totalV-1; route++){
		if(0 == p[route]){
			fprintf(file, "\t\t%c\t\t%c\n", letters[route-1], letters[route-1]); 
		}
		else{
			fprintf(file, "\t\t%c\t\t%c\n", letters[route-1], letters[p[route]-1]);
		}
	}
	
	fprintf(file, "Messages Sent:\n");
	for(int value = 0; value < totalV-1; value++){
		fprintf(file, "{A,%c,%d};", letters[value], d[value+1]);
	}
	fprintf(file, "\n");
	
}


int main(int argc, char** argv){
	//file pointer
	FILE *fp, *write;
	char buff[SIZE], letters[SIZE], distance[SIZE], messages[SIZE], nletters[SIZE], number[SIZE], bellman[SIZE], initial[SIZE];
	char num[3];
	int time = 0, node = 0, index = 0, vert = 0;
	char *test = NULL;
	
	if((fp=fopen(argv[1], "r"))==NULL){
		perror("File Can't Open\n");
		return -1;
	}
	if((write=fopen("results.txt", "w+")) == NULL){
		perror("File Can't Open\n");
		return -1;
	}
	memset(buff, 0, SIZE);
	memset(letters, 0, SIZE);
	memset(distance, 0, SIZE);
	memset(messages, 0, SIZE);
	memset(nletters, 0, SIZE);
	memset(bellman, 0, SIZE);
	struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
	g->E = 0;
	
	while (NULL != fgets(buff, SIZE, (FILE*)fp)){
		
		if(0 == time){
			//formating for the table, Basically the same for each passby
			printTableHead(write, time);
			bellman[node] = 'A';
			bellman[node+1] = '0';
			vert += 2;
			printf("%s\n", bellman);
			//we get the first line
			for(int i = 0; i < sizeof(buff); i++){
				//since the top string is seperated by comma we can seperate by comma
				if('\n' == buff[i]){
					i = sizeof(buff);
				}
				else if(0 == i){
				//the first letter to add
					letters[node] = buff[i];
					bellman[vert] = buff[i];
					//Adding the node number value into the list used for the algo
					strcpy(nletters, bellman);
					snprintf(bellman, sizeof(letters), "%s%d",nletters, node+1);
					fprintf(write, "\t\t\t%c", buff[i]);
					if(node+1 > 9){
							vert += 3;	
						}
					else{
						vert += 2;	
					}
					node += 1;
					g->V = node+1;
				}
				
				else if(',' == buff[i]){
					letters[node] = buff[i+2];
					bellman[vert] = buff[i+2];
					//Adding the node number value into the list used for the algo
					strcpy(nletters, bellman);
					snprintf(bellman, sizeof(letters), "%s%d",nletters, node+1);
					if(node+1 > 9){
							vert += 3;	
						}
					else{
						vert += 2;	
					}
					node += 1;
					distance[index] = buff[i];
					index += 1;
					fprintf(write, "\t%c", buff[i+2]);
				}
				else if(('=' == buff[i])||(' ' == buff[i]) || (58 < buff[i])){
					;
				}
				else{
					//number for the distance
					distance[index] = buff[i];
					index += 1;
					}
				}
			distance[index] = ',';
			index = 0;
			int index2 = 0;
			memset(initial, 0, SIZE);
			initial[index2] = ';';
			index2 += 1;
			for(int q = 1; q < sizeof(initial); q++){
				if(distance[index] == 0){
					q = sizeof(initial);	
				}
				else{
					initial[index2] = q +'0';
					index2 += 1;
					initial[index2] = ',';
					index2 += 1;
					while(',' != distance[index]){
						initial[index2] = distance[index];
						index2 += 1;
						index += 1;
					}
					initial[index2] = ';';
					index2 += 1;
					index += 1;
				}
			}
			initial[index2-1] = '*';
			printf("%s\n", initial);
			printf("%s\n", distance);
			fprintf(write, "\n");
			index = 0;
			int line = 0;
			int temp = 0;
			//Go line by line to print the table using the letters and distance array
			for(int i = 0; i < sizeof(letters); i++){
				if(0 == letters[i]){
					i = sizeof(letters);	
				}
				else{
					fprintf(write, "\t\t%c\t", letters[i]);
					for(temp = 0; temp < line; temp++){
						fprintf(write, "--\t");	
					}
					while(',' != distance[index]){
						fprintf(write, "%c", distance[index]);
						index += 1;
					}
					temp = i;
					while(0 != letters[temp+1]){
						fprintf(write, "\t--");
						temp += 1;
					}
					index += 1;
					line += 1;
					fprintf(write, "\n");
				}
			}
			fprintf(write,"\n\tRouting Table: \n\t\tRouting Table for A:\n\t\t--------------------\n\t\tDest\tNxtHp\n");
			for(int i = 0; i < sizeof(letters); i++){
				if(0 == letters[i]){
					i = sizeof(letters);	
				}
				else{
					fprintf(write, "\t\t%c\t\t%c\n", letters[i], letters[i]);	
				}
			}
			fprintf(write, "Messages Sent:\n");
			int tempvariable = 0;
			for(int w = 0; w < sizeof(letters); w++){
				if(0 == letters[w]){
					w = sizeof(letters);	
				}
				else{
					fprintf(write, "{A,%c,", letters[w]);
					while((47 < distance[tempvariable]) && (58 > distance[tempvariable])){
						fprintf(write, "%c", distance[tempvariable]);
						tempvariable += 1;	
					}
					tempvariable += 1;
					fprintf(write, "};");
				}
			}
			fprintf(write, "\n");
		}
		//done printing first table
		else{
		//else if (time <= 2){
		//not the first line
			printTableHead(write, time);
			
			//Parse the new line, find all of the letters
			//put the messages into an array
			int temp;
			index = 0;
			g->E = 0;
			for(int i = 0; i < sizeof(buff); i++){
				if(0 == buff[i]){
					//end of the line
					i = sizeof(buff);
				}
				else if('{' == buff[i]){
					temp = i;
					while((';' != buff[temp])){
						messages[index] = buff[temp];
						index += 1;
						temp += 1;
					}
					g->E += 1;
				}
				
				else if(',' == buff[i] && ',' == buff[i+2]){
					//check for if the letter exist
					char letter = buff[i+1];
					char prev = buff[i-1];
					int check = 0;
					int check2 = 0;
					for(temp = 0; temp < sizeof(letters); temp++){
						if(0 == letters[temp]){
							temp = sizeof(letters);
						}
						if(letter == letters[temp]){
							check = 1414;
							temp = sizeof(letters);
						}
					}
					for(temp = 0; temp < sizeof(letters); temp++){
						if(0 == letters[temp]){
							temp = sizeof(letters);
						}
						if(prev == letters[temp]){
							check2 = 1414;
							temp = sizeof(letters);
						}
					}
					if(1414 != check && 'A' != letter){
						letters[node] = letter;
						bellman[vert] = letter;
						strcpy(nletters, bellman);
						snprintf(bellman, sizeof(letters), "%s%d",nletters, node+1);
						if(node+1 > 9){
							vert += 3;	
						}
						else{
							vert += 2;	
						}
						node += 1;
						g->V = node+1;
					}
					if(1414 != check2 && 'A' != prev){
						letters[node] = prev;
						bellman[vert] = prev;
						strcpy(nletters, bellman);
						snprintf(bellman, sizeof(letters), "%s%d",nletters, node+1);
						if(node+1 > 9){
							vert += 3;	
						}
						else{
							vert += 2;	
						}
						node += 1;
						g->V = node+1;
					}
				}
				
				else{
				;	
				}
			}
			//done getting the messages and letters
			int count = 0;
			index = 0;
			memset(number, 0, SIZE);
			g->edge = (struct Edge *)malloc(g->E * sizeof(struct Edge));
			printf("%s\n", messages);
			for (int n = 0; n < sizeof(messages); n++){
				if(0 == messages[n]){
					n = sizeof(messages);	
				}
				else if('{' == messages[n]){
					//need to grab the int index vlaues of the letters
					for(int j = 0; j < sizeof(bellman); j++){
						if(0 == bellman[j]){
							j = sizeof(bellman);	
						}
						else if(messages[n+1] == bellman[j]){
							//found the start letter
							//find the index
							memset(num, 0, 3);
							for(int s=1; s<4; s++){
								if((47 < bellman[j+s]) && (58 > bellman[j+s])){
									num[s-1] = bellman[j+s];
								}
							}
							//number should be in num variable
							g->edge[count].start = atoi(num);
							memset(num, 0, 3);
						}
						else if(messages[n+3] == bellman[j]){
							//found the start letter
							//find the index
							memset(num, 0, 3);
							for(int s=1; s<4; s++){
								if((47 < bellman[j+s]) && (58 > bellman[j+s])){
									num[s-1] = bellman[j+s];
								}
							}
							//number should be in num variable
							g->edge[count].end = atoi(num);
							memset(num, 0, 3);
						}

					}
				}
				else if((47 < messages[n]) && (58 > messages[n])){
					//number found
					number[index] = messages[n];
					index += 1;
				}
				else if('}' == messages[n]){
					test = (char*) malloc((index+1)*sizeof(char));
					if(test == NULL){
						perror("Bad allocation of memory");
						return 0;
					}
					for(int x = 0; x < index; x++){
						test[x] = number[x];
					}
					g->edge[count].weight = atoi(test);
					free(test);
					count += 1;
					index = 0;
					memset(number, 0, SIZE);
				}

			}
			//edges are in the graph
			bellmanford(g, 'A', initial, write, letters);
			//printf("%s\n", bellman);
			//printf("%s\n", letters);
			//printf("%s\n", nletters);
			
		}
	time += 1;	
		
	memset(buff, 0, SIZE);
	memset(distance, 0, SIZE);
	memset(nletters, 0, SIZE);
	memset(messages, 0, SIZE);
		
	}
	fclose(fp);
	fclose(write);
	}
			

