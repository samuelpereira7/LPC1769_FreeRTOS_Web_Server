import { Component, OnInit } from '@angular/core';
import { PlaneService } from './plane.service';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
    title = 'app';
    x: number = -8;
    y: number = 0;
    z: number = 95;
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
        }, 1000);
    }

    parseServerResponse (data) {
        this.x = data.x;
        this.y = data.y;
        this.temp = data.t;
    }
}
