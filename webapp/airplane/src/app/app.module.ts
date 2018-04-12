import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';


import { AppComponent } from './app.component';
import { PlaneComponent } from './plane/plane.component';
import { SkyComponent } from './sky/sky.component';


@NgModule({
  declarations: [
    AppComponent,
    PlaneComponent,
    SkyComponent
  ],
  imports: [
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
