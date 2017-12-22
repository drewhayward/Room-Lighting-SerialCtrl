import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { StripControllerComponent } from './strip-controller/strip-controller.component';
import { StripListComponent } from './strip-list/strip-list.component';


@NgModule({
  declarations: [
    AppComponent,
    StripControllerComponent,
    StripListComponent
  ],
  imports: [
    BrowserModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
