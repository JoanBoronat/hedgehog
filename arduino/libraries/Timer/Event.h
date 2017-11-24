/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*************************************************************************************
* Nom del fitxer: Event.h		    	                              	      		 *
* Data: 02/XII/2013							      							  		 *
* Autor: David Gamez Alari (david.gameza@urv.cat)			       			  		 *
* Descripci�: llibreria per a la realitzaci� de la pr�ctica de l'assignatura  		 *
*	Aplicacions M�bils i Encastades, gestor d'esdeveniments de l'aplicaci� encastada *
* Universitat Rovira i Virgili						           				  		 *
* Departament d'Enginyeria Inform�tica i Matem�tiques			      		  		 *
**************************************************************************************/

#ifndef Event_h
#define Event_h

#include <inttypes.h>

#define EVENT_NONE 0
#define EVENT_EVERY 1
#define EVENT_OSCILLATE 2

class Event
{

public:
  Event(void);
  void update(void);
  int8_t eventType;
  unsigned long period;
  int repeatCount;
  uint8_t pin;
  uint8_t pinState;
  void (*callback)(void*);
  unsigned long lastEventTime;
  int count;
  void* context;
};

#endif
