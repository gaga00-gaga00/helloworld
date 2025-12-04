#pragma once
#ifndef LISTWORK_H
#define LISTWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct ListWork {
	int num;
	char Subject[30];
	char workname[50];
	int year;
	int month;
	int day;
	int hour;
	int minu;
	int second;
	char send[6];
	struct ListWork* next;
	int change;
}listwork;

typedef struct LinkedList {
	listwork* head;
	int length;
}linkedlist;

void OpenMyFile(linkedlist* L);
void SaveMyFile(linkedlist* L);
int MonthtoDay(int wyear, int wmonth);
void LastTime(listwork w);
void CheckAlarm(linkedlist* L, int systemAL);
void displayList(linkedlist* L);
void insertList(linkedlist* L, listwork w);
void AddWork(linkedlist* L, int* autoNumber);
void DeleteWork(linkedlist* L, int* autoNumber);
void ReWork(linkedlist* L);
void ZungRrull(linkedlist* L);
void LastClear(linkedlist* L, int* autoNumber);


#endif
