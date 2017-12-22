import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { StripControllerComponent } from './strip-controller.component';

describe('StripControllerComponent', () => {
  let component: StripControllerComponent;
  let fixture: ComponentFixture<StripControllerComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ StripControllerComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(StripControllerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
