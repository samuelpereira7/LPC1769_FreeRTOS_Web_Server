import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable()
export class PlaneService {

  configUrl = '192.168.0.87'

  constructor(private http: HttpClient) { }

  getAirplane() {
    return this.http.get(this.configUrl);
  }

}
