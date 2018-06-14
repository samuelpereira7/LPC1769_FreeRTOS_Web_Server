import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';


import { AppComponent } from './app.component';
import { PlaneComponent } from './plane/plane.component';
import { SkyComponent } from './sky/sky.component';
import {
  IMqttMessage,
  MqttModule,
  IMqttServiceOptions,
  MqttService,
} from 'ngx-mqtt';

export const MQTT_SERVICE_OPTIONS: IMqttServiceOptions = {
  hostname: 'localhost',
  port: 9001,
  path: '/mqtt',
};

export function mqttServiceFactory() {
  return new MqttService(MQTT_SERVICE_OPTIONS);
}

@NgModule({
  declarations: [
    AppComponent,
    PlaneComponent,
    SkyComponent
  ],
  imports: [
    BrowserModule,
    MqttModule.forRoot({
      provide: MqttService,
      useFactory: mqttServiceFactory
    })
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
