import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { of } from 'rxjs/observable/of';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { LightStrip } from '.lightStrip';
import { LightSwitched } from '.lightSwitched';

@Injectable()
export class LightControllerService {
  // Temporary constant return values
  CONST lightStrips: LightStrip[] = [
    {name:'Bed', key='bedStrip', color='#af3000'},
    {name:'Closet', key='closetStrip', color='#afff00'}
  ]
  CONST switchedLights: LightSwitched[] = [
    {name: 'Desk Lamp', key='deskLamp', state=1},
    {name: 'Standing lamp', key='standingLamp', state=1},
    {name: 'Christmas Lights', key='christmas', state=1}
  ]

  constructor() { }

  getStripsState(): Observable<LightStrip[]>{
    console.log("Fetching LED strip states");
    return of(lightStrips);
  }

  getSwitchedLightsState(): Observable<LightSwitched[]>{
    console.log("Fetching switched light states");
    return of(switchedLights);
  }

  
}
