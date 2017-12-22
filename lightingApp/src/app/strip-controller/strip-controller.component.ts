import { Component, OnInit } from '@angular/core';
import { LightStrip } from '.LightStrip';

@Component({
  selector: 'app-strip-controller',
  templateUrl: './strip-controller.component.html',
  styleUrls: ['./strip-controller.component.css']
})
export class StripControllerComponent implements OnInit {
  lightStrip: LightStrip;

  constructor() {

  }

  ngOnInit() {
    this.lightStrip.name = "Name";
    this.lightStrip.color = "#ffffff";
  }

}
