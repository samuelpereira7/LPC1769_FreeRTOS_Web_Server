import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable()
export class PlaneService {
  configUrl = 'http://localhost:5200/'

  constructor(private http: HttpClient) { }

  getAirplane() {
    return this.http.get(this.configUrl);
  }

}
