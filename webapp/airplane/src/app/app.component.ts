import { Component, OnInit } from '@angular/core';
import { PlaneService } from './plane.service';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
    title = 'app';
    x: number = 10;
    y: number = 90;
    z: number = -20;
    temp: number = 0;

    constructor (
        private planeService: PlaneService
    ) {

    }

    ngOnInit() {
        setInterval(() => {
           this.planeService.getAirplane().subscribe(
               (res) => this.parseServerResponse(res),
               (error) => console.log('error:' + error)
           ); 
        }, 10000);
    }


    parseServerResponse (data) {
        const splittedData = data.split(',');
        this.x = splittedData[0];
        this.y = splittedData[1];
        this.z = splittedData[2];
        this.temp = splittedData[3];
    }


}
