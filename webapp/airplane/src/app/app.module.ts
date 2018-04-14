import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';


import { AppComponent } from './app.component';
import { PlaneComponent } from './plane/plane.component';
import { SkyComponent } from './sky/sky.component';
import { PlaneService } from './plane.service';
import { HttpClientModule } from '@angular/common/http';


@NgModule({
  declarations: [
    AppComponent,
    PlaneComponent,
    SkyComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule
  ],
  providers: [PlaneService],
  bootstrap: [AppComponent]
})
export class AppModule { }
