import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { SkyComponent } from './sky.component';

describe('SkyComponent', () => {
  let component: SkyComponent;
  let fixture: ComponentFixture<SkyComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ SkyComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(SkyComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
