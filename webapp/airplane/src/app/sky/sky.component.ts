import { Component, Input } from '@angular/core';

@Component({
    selector: 'app-sky',
    templateUrl: './sky.component.html',
    styleUrls: ['./sky.component.css']
})
export class SkyComponent {

    @Input() temp = 350;

    constructor() { }

}
