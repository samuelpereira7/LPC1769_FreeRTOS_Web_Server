import { Component, OnInit } from '@angular/core';
import { PlaneService } from './plane.service';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
    title = 'app';
    x = -8;
    y = 0;
    z = 95;
    temp = 150;

    constructor(
        private planeService: PlaneService
    ) {

    }

    ngOnInit() {
        setInterval(() => {
            // Realiza requisição ao servidor
            this.planeService.getAirplane().subscribe(
                // Requisição realizada com sucesso
                (res) => this.parseServerResponse(res),
                // Erro ao realizar requisição
                (error) => console.log('error:' + error)
            );
        }, 1000);
    }

    // Faz o parse dos dados recebidos
    parseServerResponse(data) {
        this.x = data.x;
        this.y = data.y;
        this.temp = data.t;
    }
}
