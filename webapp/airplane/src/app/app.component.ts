import { Component, OnDestroy } from '@angular/core';
import { MqttService, IMqttMessage } from 'ngx-mqtt';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.css']
})
export class AppComponent implements OnDestroy {
    title = 'app';
    x = -8;
    y = 0;
    z = 95;
    temp = 150;
    subscription: any;

    constructor(
        private mqttService: MqttService
    ) {
        this.subscription = this.mqttService.observe('plane').subscribe((message: IMqttMessage) => {
            this.parseServerResponse(message.payload);
        });
    }

    ngOnDestroy() {
        this.subscription.unsubscribe();
    }

    // Faz o parse dos dados recebidos
    parseServerResponse(data) {
        this.x = data.x;
        this.y = data.y;
        this.temp = data.t;
    }
}
