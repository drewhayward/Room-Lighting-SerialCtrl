import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { StripListComponent } from './strip-list.component';

describe('StripListComponent', () => {
  let component: StripListComponent;
  let fixture: ComponentFixture<StripListComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ StripListComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(StripListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
