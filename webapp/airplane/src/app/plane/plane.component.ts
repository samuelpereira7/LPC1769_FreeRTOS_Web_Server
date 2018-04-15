import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: 'app-plane',
  templateUrl: './plane.component.html',
  styleUrls: ['./plane.component.css']
})
export class PlaneComponent implements OnInit {

  @Input() x: number = 0
  @Input() y: number = 0
  @Input() z: number = 0
  @Input() temp: number = 0

  constructor() { }

  ngOnInit() {
  }

}
