import { Component, Input } from '@angular/core';

@Component({
    selector: 'app-plane',
    templateUrl: './plane.component.html',
    styleUrls: ['./plane.component.css']
})
export class PlaneComponent {

    @Input() x = 0;
    @Input() y = 0;
    @Input() z = 0;

    constructor() { }

}
