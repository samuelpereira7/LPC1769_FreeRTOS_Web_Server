import { TestBed, inject } from '@angular/core/testing';

import { PlaneService } from './plane.service';

describe('PlaneService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [PlaneService]
    });
  });

  it('should be created', inject([PlaneService], (service: PlaneService) => {
    expect(service).toBeTruthy();
  }));
});
