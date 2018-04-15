import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PlaneComponent } from './plane.component';

describe('PlaneComponent', () => {
  let component: PlaneComponent;
  let fixture: ComponentFixture<PlaneComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PlaneComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PlaneComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
