import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { map } from 'rxjs/operators';
import { IProduct } from './product';
import { ProductService } from './product.service';

@Component({  
  templateUrl: './product-detail.component.html',
  styleUrls: ['./product-detail.component.css']
})
export class ProductDetailComponent implements OnInit {

  pageTitle: string = 'Product Detail';
  product: IProduct;  

  constructor(private route: ActivatedRoute,
              private router: Router,
              private productService: ProductService) { 

  }

  ngOnInit(): void {
    let id = +this.route.snapshot.paramMap.get('id');
    this.pageTitle += `: ${id}`;
    this.productService.getProduct(id).subscribe({
      next: product => this.product = product,
      error: err => alert(err)
    });
  }

  onBack(): void {
    this.router.navigate(['/products']);
  }
}
